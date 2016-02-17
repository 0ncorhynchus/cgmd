#include "stabilize_stepper.hpp"
#include <limits>
#include <cmath>

namespace cgmd {

StabilizeStepper::StabilizeStepper(std::shared_ptr<Space> space,
        std::shared_ptr<Model> model, double dx) :
    _space(space), _model(model), _dx(dx) {
    const std::size_t num_beads(_space->num_beads());
    _dt = 0;
    _mass_list = std::vector<double>(num_beads);

    initialize_parameters();

}

void StabilizeStepper::initialize_parameters() {
    for (std::size_t id(0); id < _space->num_beads(); ++id) {
        _mass_list[id] = _model->get_mass(id);
    }
}

void StabilizeStepper::initialize_neighbor_list_managers() {
    const std::size_t num_beads(_space->num_beads());

    PairList bond_pair(num_beads);
    std::list<std::pair<std::size_t, std::size_t> > bonds(_model->list_bonds());
    for (auto itr(bonds.begin()); itr != bonds.end(); itr++) {
        bond_pair.add_pair(*itr);
        bond_pair.add_pair(std::make_pair((*itr).second, (*itr).first));
    }

    PairList excludes(num_beads);
    for (std::size_t i(0); i < num_beads; ++i) {
        for (auto itr(bond_pair.begin(i)); itr != bond_pair.end(i); ++itr) {
            excludes.add_pair(std::make_pair(i, *itr));
            for (auto jtr(bond_pair.begin(*itr)); jtr != bond_pair.end(*itr); ++jtr) {
                excludes.add_pair(std::make_pair(i, *jtr));
            }
        }
    }

    Model::inter_potential_container inter_potentials(_model->list_inter_potentials());
    for (auto itr(inter_potentials.begin()); itr != inter_potentials.end(); ++itr) {
        const double r_c((*itr)->get_cutoff_radius());
        NeighborListManager manager(num_beads, r_c, r_c*3,
                std::numeric_limits<double>::infinity()); // TODO parameter fitting
        (*itr)->set_neighbor_list(manager.get_neighbor_list());
        for (std::size_t i(0); i < num_beads-1; ++i) {
            std::string symbol0(_space->symbol(i));
            for (std::size_t j(i+1); j < num_beads; j++) {
                std::string symbol1(_space->symbol(j));
                if ((*itr)->is_valid_pair(symbol0, symbol1)) {
                    bool is_exclude(false);
                    for (auto itr2(excludes.begin(i)); itr2 != excludes.end(i); ++itr2)
                        if (j == *itr2) {
                            is_exclude = true;
                            break;
                        }
                    if (!is_exclude)
                        manager.add_candidate(std::make_pair(i,j));
                }
            }
        }
        manager.update(*(_space.get()));
        _neighbor_list_managers.push_back(manager);
    }
}

void StabilizeStepper::step() {
    const std::size_t num_beads(_space->num_beads());

    // Calculate Force
    vector_list acceleration(num_beads, Vector3d(0,0,0));
    const vector_list force_list(_model->calculate_force(*(_space.get())));
    double max_accel(0);
    for (std::size_t i(0); i < num_beads; ++i) {
        acceleration[i] = force_list.at(i) / _mass_list.at(i);
        if (norm(acceleration[i]) > max_accel)
            max_accel = norm(acceleration[i]);
    }

    // Calculate delta
    _dt = sqrt(_dx/max_accel)/2;

    // Update Coordinate
    std::list<double> displacements;
    for (std::size_t i(0); i < num_beads; ++i) {
        const Vector3d direction(acceleration.at(i) * _dt*_dt/2);
        _space->move(i, direction);
        displacements.push_back(norm(direction));
    }

    // Update NeighborList
    for (auto itr(_neighbor_list_managers.begin()); itr != _neighbor_list_managers.end(); ++itr) {
        (*itr).add_displacements(displacements);
        if ((*itr).to_update(_space->t()))
            (*itr).update(*(_space.get()));
    }

    _space->set_t(_space->t() + _dt);
}

double StabilizeStepper::dt() const {
    return _dt;
}

} // cgmd
