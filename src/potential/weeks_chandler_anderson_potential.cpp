#include "weeks_chandler_anderson_potential.hpp"
#include <cmath>

namespace cgmd {

WeeksChandlerAndersonPotential::WeeksChandlerAndersonPotential(double sigma, double epsilon) :
        LennardJonesPotential(sigma, epsilon),
        _cutoff_radius(pow(2,1.0/6.0)*sigma) {
}

double WeeksChandlerAndersonPotential::calculate_unit_energy(double distance) const {
    if (distance > _cutoff_radius)
        return 0.0;
    return LennardJonesPotential::calculate_unit_energy(distance) + _epsilon;
}

Vector3d WeeksChandlerAndersonPotential::calculate_unit_force(const Vector3d& vec) const {
    if (norm(vec) > _cutoff_radius)
        return Vector3d(0,0,0);
    return LennardJonesPotential::calculate_unit_force(vec);
}

double WeeksChandlerAndersonPotential::get_cutoff_radius() const {
    return _cutoff_radius;
}

} // cgmd
