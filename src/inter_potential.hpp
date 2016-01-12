#ifndef __INTER_POTENTIAL_HPP
#define __INTER_POTENTIAL_HPP

#include "potential.hpp"

class InterPotential : public Potential {
public:
    virtual double calculate_energy(const Space& space) const = 0;
    virtual vector_list calculate_force(const Space& space) const = 0;
};

#endif
