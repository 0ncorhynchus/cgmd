#include "space.hpp"

namespace cgmd {

Space::Space() {}

Space::Space(const std::size_t& size) {
    reset(size);
}

void Space::reset(const std::size_t& size) {
    _symbols.clear();
    _coordinates.clear();
    _velocities.clear();

    _symbols.resize(size, "");
    _coordinates.resize(size, Vector3d(0,0,0));
    _velocities.resize(size, Vector3d(0,0,0));

    _t = 0;
}

void Space::initialize() {}

std::string& Space::symbol(std::size_t index) {
    return _symbols.at(index);
}

const std::string& Space::symbol(std::size_t index) const {
    return _symbols.at(index);
}

Vector3d& Space::coordinate(std::size_t index) {
    return _coordinates.at(index);
}

const Vector3d& Space::coordinate(std::size_t index) const {
    return _coordinates.at(index);
}

void Space::move(std::size_t index, const Vector3d& direction) {
    _coordinates.at(index) += direction;
}

Vector3d& Space::velocity(std::size_t index) {
    return _velocities.at(index);
}

const Vector3d& Space::velocity(std::size_t index) const {
    return _velocities.at(index);
}

Vector3d Space::direct(std::size_t i, std::size_t j) const {
    return _coordinates.at(j) - _coordinates.at(i);
}

double Space::distance(std::size_t i, std::size_t j) const {
    return norm(direct(i,j));
}

} // cgmd
