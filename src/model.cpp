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

bool Model::is_in_range(const std::size_t& id) const {
    return (id >= 0 && id < _property_list.size());
}

double Model::get_mass(const std::size_t& id) const {
    if (!is_in_range(id))
        return 0.0; // Throwing the Exception is better.
    return _property_list.at(id).first;
}

double Model::get_friction(const std::size_t& id) const {
    if (!is_in_range(id))
        return 0.0; // Throwing the Exception is better.
    return _property_list.at(id).second;
}

void Model::add_potential(std::shared_ptr<Potential> potential) {
    _potentials.push_back(potential);
}

bool Model::remove_potential(const std::size_t& i) {
    if (i < 0 || i >= _potentials.size())
        return false;
    _potentials.erase(_potentials.begin()+i);
    return true;
}

const Model::potential_container& Model::list_potentials() const {
    return _potentials;
}

