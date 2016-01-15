#include "langevin_stepper.hpp"
#include "constants.hpp"
#include <memory>
#include <math.h>

namespace cgmd {

LangevinStepper::LangevinStepper() : _dt(0), _T(0) {
}

LangevinStepper::LangevinStepper(const LangevinStepper& stepper)
        : _dt(stepper._dt), _T(stepper._T) {
#define COPY_VECTOR(VAR) \
    copy(stepper.VAR.begin(), stepper.VAR.end(), back_inserter(VAR))
    COPY_VECTOR(_acceleration_list);
    COPY_VECTOR(_deviation);
    COPY_VECTOR(_const_term2);
    COPY_VECTOR(_const_term3);
    COPY_VECTOR(_const_term4);
    COPY_VECTOR(_mass_list);
    COPY_VECTOR(_neighbor_list_managers);
#undef COPY_VECTOR
}

LangevinStepper::LangevinStepper(std::shared_ptr<Space> space,
    std::shared_ptr<Model> model, std::mt19937 random_generator, double dt, double T) :
    _space(space), _model(model), _dist(0,1), _gen(random_generator), _dt(dt), _T(T) {
    const std::size_t num_beads(_space->num_beads());

    _acceleration_list = vector_list(num_beads, Vector3d(0,0,0));
    _deviation = std::vector<double>(num_beads);
    _const_term2 = std::vector<double>(num_beads);
    _const_term3 = std::vector<double>(num_beads);
    _const_term4 = std::vector<double>(num_beads);
    _mass_list = std::vector<double>(num_beads);

    initialize_parameters();
    initialize_neighbor_list_managers();
}

void LangevinStepper::initialize_parameters() {
    const std::size_t num_beads(_space->num_beads());
    for (std::size_t id(0); id < num_beads; ++id) {
        const double friction(_model->get_friction(id));
        const double mass(_model->get_mass(id));
        _deviation[id] = sqrt(2*friction*kB*_T/mass/_dt);
        _const_term2[id] = (1-friction*_dt/2)*(1-friction*_dt/2+pow(friction*_dt/2,2));
        _const_term3[id] = _dt/2*(1-friction*_dt/2);
        _const_term4[id] = _dt*(1-friction*_dt/2);
        _mass_list[id] = mass;
    }

}

void LangevinStepper::initialize_neighbor_list_managers() {
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
        NeighborListManager manager(num_beads, r_c, r_c*3, _dt*20); // TODO parameter fitting
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

void LangevinStepper::step() {
    const std::size_t num_beads(_space->num_beads());

    // Update Coordinate
    std::list<double> displacements;
    for (std::size_t i(0); i < num_beads; ++i) {
        const Vector3d move(_space->velocity(i) * _const_term4.at(i)
                + _acceleration_list.at(i) * _dt*_dt/2);
        _space->coordinate(i) += move;
        displacements.push_back(norm(move));
    }

    // Update NeighborList
    for (auto itr(_neighbor_list_managers.begin()); itr != _neighbor_list_managers.end(); ++itr) {
        (*itr).add_displacements(displacements);
        if ((*itr).to_update(_space->t()))
            (*itr).update(*(_space.get()));
    }

    // Update Force
    vector_list new_acceleration(num_beads, Vector3d(0,0,0));
    const vector_list force_list(_model->calculate_force(*(_space.get())));
    for (std::size_t i(0); i < num_beads; ++i) {
        new_acceleration[i] = force_list.at(i) / _mass_list.at(i)
            + get_unit_random_force() * _deviation.at(i);
    }

    // Update Velocity
    for (std::size_t i(0); i < num_beads; ++i)
        _space->velocity(i) = _space->velocity(i) * _const_term2.at(i)
            + (_acceleration_list.at(i) + new_acceleration.at(i)) * _const_term3.at(i);

    _space->set_t(_space->t() + _dt);
    _acceleration_list = new_acceleration;
}

double LangevinStepper::get_unit_white_noise() {
    return _dist(_gen);
}

Vector3d LangevinStepper::get_unit_random_force() {
    const double r(get_unit_white_noise());
    const double t(get_unit_white_noise() * M_PI);
    const double p(get_unit_white_noise() * M_PI * 2);
    return Vector3d(
            r * sin(t) * cos(p),
            r * sin(t) * sin(p),
            r * cos(t));
}

} // cgmd
