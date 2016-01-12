#ifndef __INTRA_POTENTIAL_HPP
#define __INTRA_POTENTIAL_HPP

#include "potential.hpp"

class IntraPotential : public Potential {
public:
    virtual double calculate_energy(const Space& space) const = 0;
    virtual vector_list calculate_force(const Space& space) const = 0;
};

#endif
