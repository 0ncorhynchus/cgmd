#ifndef __WEEKS_CHANDLER_ANDERSON_POTENTIAL_HPP
#define __WEEKS_CHANDLER_ANDERSON_POTENTIAL_HPP

#include "lennard_jones_potential.hpp"

class WeeksChandlerAndersonPotential : public LennardJonesPotential {
public:
    WeeksChandlerAndersonPotential(double sigma, double epsilon);
    double calculate_unit_energy(double distance) const;
    Vector3d calculate_unit_force(const Vector3d& vec) const;

protected:
    const double _cutoff_radius;
};

#endif /* __WEEKS_CHANDLER_ANDERSON_POTENTIAL_HPP */
