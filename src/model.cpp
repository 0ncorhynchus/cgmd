#include "model.hpp"

Model::Model() {}

Model::Model(std::size_t size) {
    reset(size);
}

void Model::reset(const std::size_t& size) {
    _property_list.clear();
    _property_list.resize(size, std::make_pair(0.0, 0.0));
    _bond_potentials.clear();
    _potentials.clear();
}

void Model::set_property(const std::size_t& id, double mass, double friction) {
    _property_list.at(id) = std::make_pair(mass, friction);
}

double Model::get_mass(const std::size_t& id) const {
    return _property_list.at(id).first;
}

double Model::get_friction(const std::size_t& id) const {
    return _property_list.at(id).second;
}

double Model::calculate_energy(const Space& space) const {
    double energy(0.0);
    for (auto itr(_bond_potentials.begin()); itr != _bond_potentials.end(); ++itr) {
        energy += (*itr)->calculate_energy(space);
    }
    for (auto itr(_potentials.begin()); itr != _potentials.end(); ++itr) {
        energy += (*itr)->calculate_energy(space);
    }
    return energy;
}

vector_list Model::calculate_force(const Space& space) const {
    vector_list forces(space.num_beads(), Vector3d(0,0,0));
    for (auto itr(_bond_potentials.begin()); itr != _bond_potentials.end(); ++itr) {
        forces += (*itr)->calculate_force(space);
    }
    for (auto itr(_potentials.begin()); itr != _potentials.end(); ++itr) {
        forces += (*itr)->calculate_force(space);
    }
    return forces;
}

void Model::add_potential(std::shared_ptr<Potential> potential) {
    std::shared_ptr<BondPotential> bond_ptr(std::dynamic_pointer_cast<BondPotential>(potential));
    if (bond_ptr != nullptr) {
        _bond_potentials.push_back(bond_ptr);
        return;
    }

    std::shared_ptr<InterPotential> inter_ptr(std::dynamic_pointer_cast<InterPotential>(potential));
    if (inter_ptr != nullptr) {
        _inter_potentials.push_back(inter_ptr);
        return;
    }

    _potentials.push_back(potential);
}

std::list<std::pair<std::size_t, std::size_t> > Model::list_bonds() const {
    std::list<std::pair<std::size_t, std::size_t> > bonds;
    for (auto itr(_bond_potentials.begin()); itr != _bond_potentials.end(); ++itr) {
        bonds.splice(bonds.end(), (*itr)->list_bonds());
    }
    return bonds;
}

Model::inter_potential_container& Model::list_inter_potentials() {
    return _inter_potentials;
}
