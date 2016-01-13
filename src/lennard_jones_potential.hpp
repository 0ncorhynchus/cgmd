#ifndef __LENNARD_JONES_POTENTIAL_HPP
#define __LENNARD_JONES_POTENTIAL_HPP

#include "inter_potential.hpp"

namespace cgmd {

class LennardJonesPotential : public InterPotential {
public:
    LennardJonesPotential(double sigma, double epsilon);
    virtual double calculate_unit_energy(double distance) const;
    virtual Vector3d calculate_unit_force(const Vector3d& vec) const;
    virtual double get_cutoff_radius() const;

protected:
    const double _sigma;
    const double _epsilon;
};

} // cgmd

#endif /* __LENNARD_JONES_POTENTIAL_HPP */
