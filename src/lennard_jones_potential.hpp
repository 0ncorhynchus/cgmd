#ifndef __LENNARD_JONES_POTENTIAL_HPP
#define __LENNARD_JONES_POTENTIAL_HPP

#include "pairwise_potential.hpp"

class LennardJonesPotential : public PairwisePotential {
public:
    LennardJonesPotential(double sigma, double epsilon);
    virtual double calculate_unit_energy(double distance) const;
    virtual Vector3d calculate_unit_force(const Vector3d& vec) const;

protected:
    const double _sigma;
    const double _epsilon;
};

#endif /* __LENNARD_JONES_POTENTIAL_HPP */
