#ifndef __WEEKS_CHANDLER_ANDERSON_POTENTIAL_HPP
#define __WEEKS_CHANDLER_ANDERSON_POTENTIAL_HPP

#include "lennard_jones_potential.hpp"

namespace cgmd {

class WeeksChandlerAndersonPotential : public LennardJonesPotential {
public:
    WeeksChandlerAndersonPotential(double sigma, double epsilon);
    double calculate_unit_energy(double distance) const;
    Vector3d calculate_unit_force(const Vector3d& vec) const;
    double get_cutoff_radius() const;

protected:
    const double _cutoff_radius;
};

} // cgmd

#endif /* __WEEKS_CHANDLER_ANDERSON_POTENTIAL_HPP */
