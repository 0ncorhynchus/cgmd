#ifndef __HARMONIC_BOND_POTENTIAL_HPP
#define __HARMONIC_BOND_POTENTIAL_HPP

#include "bond_potential.hpp"
#include <map>

namespace cgmd {

class HarmonicBondPotential : public BondPotential {
public:
    bool add_bond(const std::size_t& id0, const std::size_t& id1, double r, double k);
    double get_r(const std::size_t& id0, const std::size_t& id1) const;
    double get_k(const std::size_t& id0, const std::size_t& id1) const;
    double calculate_energy(const Space& space) const;
    vector_list calculate_force(const Space& space) const;
    std::list<std::pair<std::size_t, std::size_t> > list_bonds() const;

protected:
    std::map<std::pair<std::size_t, std::size_t>,
        std::pair<double, double> > _map;
};

} // cgmd

#endif /* __HARMONIC_BOND_POTENTIAL_HPP */
