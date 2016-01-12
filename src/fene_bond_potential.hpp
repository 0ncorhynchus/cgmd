#ifndef __FENE_BOND_POTENTIAL_HPP
#define __FENE_BOND_POTENTIAL_HPP

#include "bond_potential.hpp"
#include "weeks_chandler_anderson_potential.hpp"

class FENEBondPotential : public BondPotential {
public:
    FENEBondPotential(double r0, double k, double sigma, double epsilon);
    void add_bond(const std::pair<std::size_t, std::size_t>& pair);
    double calculate_energy(const Space& space) const;
    vector_list calculate_force(const Space& space) const;
    std::list<std::pair<std::size_t, std::size_t> > list_bond() const;

protected:
    const double _r0, _k;
    WeeksChandlerAndersonPotential _weeks_chandler_anderson;
    std::list<std::pair<std::size_t, std::size_t> > _bonds;
};

#endif /* __FENE_BOND_POTENTIAL_HPP */
