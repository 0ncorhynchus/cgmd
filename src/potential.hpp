#ifndef __FORCE_FIELD_HPP
#define __FORCE_FIELD_HPP

#include "vector3d.hpp"
#include "space.hpp"
#include <vector>
#include <map>

class Potential {
public:
    virtual double calculate_energy(const Space& space) const = 0;
    virtual vector_list calculate_force(const Space& space) const = 0;
};

class BondingPotential : public Potential {
public:
    bool add_bond(const std::size_t& id0, const std::size_t& id1, double r, double k);
    double get_r(const std::size_t& id0, const std::size_t& id1) const;
    double get_k(const std::size_t& id0, const std::size_t& id1) const;
    virtual double calculate_energy(const Space& space) const;
    virtual vector_list calculate_force(const Space& space) const;

protected:
    std::map<std::pair<std::size_t, std::size_t>,
        std::pair<double, double> > _map;
};

std::pair<std::size_t, std::size_t> make_sorted_pair(
    const std::size_t& id0, const std::size_t& id1);

#endif /* __FORCE_FIELD_HPP */
