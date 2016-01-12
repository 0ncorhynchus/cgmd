#ifndef __BOND_POTENTIAL_HPP
#define __BOND_POTENTIAL_HPP

#include "potential.hpp"
#include <list>

class BondPotential : public Potential {
public:
    virtual double calculate_energy(const Space& space) const = 0;
    virtual vector_list calculate_force(const Space& space) const = 0;
    virtual std::list<std::pair<std::size_t, std::size_t> > list_bond() const = 0;
};

#endif /* __BOND_POTENTIAL_HPP */
