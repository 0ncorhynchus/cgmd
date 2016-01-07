#include "space.hpp"

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

Vector3d& Space::velocity(std::size_t index) {
    return _velocities.at(index);
}

const Vector3d& Space::velocity(std::size_t index) const {
    return _velocities.at(index);
}
