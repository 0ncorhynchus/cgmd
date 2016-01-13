#ifndef __LOWEST_ORDER_HARMONIC_BEND_POTENTIAL_HPP
#define __LOWEST_ORDER_HARMONIC_BEND_POTENTIAL_HPP

#include <cgmd/potential.hpp>
#include <list>

namespace cgmd {

class LowestOrderHarmonicBendPotential : public Potential {
public:
    LowestOrderHarmonicBendPotential(double r0, double k);
    void add_pair(const std::pair<std::size_t, std::size_t>& pair);
    double calculate_energy(const Space& space) const;
    vector_list calculate_force(const Space& space) const;

protected:
    const double _r0, _k;
    std::list<std::pair<std::size_t, std::size_t> > _pairs;
};

} // cgmd

#endif /* __LOWEST_ORDER_HARMONIC_BEND_POTENTIAL_HPP */
