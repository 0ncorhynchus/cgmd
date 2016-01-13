#include "tails_attraction_potential.hpp"
#include <cmath>

namespace cgmd {

TailsAttractionPotential::TailsAttractionPotential(double inner_radius, double cutoff_width, double epsilon) :
        _r_c(inner_radius), _w_c(cutoff_width), _minus_epsilon(-1*epsilon) {
}

double TailsAttractionPotential::get_cutoff_radius() const {
    return _r_c + _w_c;
}

double TailsAttractionPotential::calculate_unit_energy(const double distance) const {
    if (distance < _r_c)
        return _minus_epsilon;
    if (distance > get_cutoff_radius())
        return 0;
    return _minus_epsilon * pow(cos(M_PI*(distance-_r_c)/_w_c/2),2);
}

Vector3d TailsAttractionPotential::calculate_unit_force(const Vector3d& vec) const {
    const double r(norm(vec));
    if (r < _r_c)
        return Vector3d(0,0,0);
    if (r > get_cutoff_radius())
        return Vector3d(0,0,0);
    return vec/r * _minus_epsilon * sin(M_PI*(r-_r_c)/_w_c)/2 * M_PI/_w_c;
}

} // cgmd
