#include "periodic_space.hpp"
#include <cmath>

namespace cgmd {

PeriodicSpace::PeriodicSpace() {}

PeriodicSpace::PeriodicSpace(const std::size_t size, double X, double Y, double Z) :
    Space::Space(size), _x(X), _y(Y), _z(Z) {
    initialize();
}

void PeriodicSpace::set_lengths(double X, double Y, double Z) {
    _x = fabs(X);
    _y = fabs(Y);
    _z = fabs(Z);
    initialize();
}

void PeriodicSpace::initialize() {
    for (std::size_t i(0); i < num_beads(); ++i)
        adjust(i);
}

void PeriodicSpace::move(std::size_t index, const Vector3d& direction) {
    Space::move(index, direction);
    adjust(index);
}

Vector3d PeriodicSpace::direct(std::size_t i, std::size_t j) const {
    Vector3d vec(Space::direct(i, j));

#define ADJUST(v) \
    if (vec.v > 0.5*_##v)\
        vec.v -= _##v;\
    else if(vec.v < -0.5*_##v)\
        vec.v += _##v;

    ADJUST(x)
    ADJUST(y)
    ADJUST(z)

#undef ADJUST

    return vec;
}

void PeriodicSpace::adjust(std::size_t index) {
    Vector3d& vec(_coordinates.at(index));
#define ADJUST(v) \
    if (vec.v < 0)\
        vec.v += _##v;\
    else if (vec.v >= _##v)\
        vec.v -= _##v;

    ADJUST(x)
    ADJUST(y)
    ADJUST(z)

#undef ADJUST
}

} // cgmd
