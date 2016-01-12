#include "model.hpp"

Model::Model() {}

Model::Model(std::size_t size) {
    reset(size);
}

void Model::set_dt(double dt) {
    _dt = dt;
}

void Model::reset(const std::size_t& size) {
    _property_list.clear();
    _property_list.resize(size, std::make_pair(0.0, 0.0));
}

void Model::set_property(const std::size_t& id, double mass, double friction) {
    _property_list.at(id) = std::make_pair(mass, friction);
}

double Model::get_dt() const {
    return _dt;
}

double Model::get_mass(const std::size_t& id) const {
    return _property_list.at(id).first;
}

double Model::get_friction(const std::size_t& id) const {
    return _property_list.at(id).second;
}

void Model::add_potential(std::shared_ptr<Potential> potential) {
    _potentials.push_back(potential);
}

void Model::add_potential(std::shared_ptr<InterPotential> potential) {
    _potentials.push_back(potential); //TODO
}

const Model::potential_container& Model::list_potentials() const {
    return _potentials;
}

