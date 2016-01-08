#include "lennard_jones_potential.hpp"
#include <math.h>

LennardJonesPotential::LennardJonesPotential(double sigma, double epsilon) :
    _sigma(sigma), _epsilon(epsilon) {}

double LennardJonesPotential::calculate_unit_energy(double distance) const {
    const double R6(pow(_sigma/distance, 6));
    return 4 * _epsilon * R6 * (R6 - 1);
}

Vector3d LennardJonesPotential::calculate_unit_force(const Vector3d& vec) const {
    const double r(norm(vec));
    const double R6(pow(_sigma/r, 6));
    const double strength(24 * _epsilon / r * R6 * (2*R6 - 1));
    return vec / r * strength;
}
