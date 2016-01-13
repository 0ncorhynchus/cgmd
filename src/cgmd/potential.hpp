#ifndef __POTENTIAL_HPP
#define __POTENTIAL_HPP

#include "vector3d.hpp"
#include "space.hpp"
#include "pair_list.hpp"
#include <map>
#include <memory>
#include <string>

namespace cgmd {

class Potential {
public:
    virtual double calculate_energy(const Space& space) const = 0;
    virtual vector_list calculate_force(const Space& space) const = 0;
};

class BondPotential : public Potential {
public:
    virtual double calculate_energy(const Space& space) const = 0;
    virtual vector_list calculate_force(const Space& space) const = 0;
    virtual std::list<std::pair<std::size_t, std::size_t> > list_bonds() const = 0;
};

/*
 * This class is for pairwise potentials
 */
class InterPotential : public Potential{
public:
    double calculate_energy(const Space& space) const;
    vector_list calculate_force(const Space& space) const;

    void set_neighbor_list(std::shared_ptr<PairList> neighbor_list);

    void set_pair(std::string symbol0, std::string symbol1);
    std::pair<std::string, std::string> get_pair() const;
    bool is_valid_pair(std::string symbol0, std::string symbol1) const;

    virtual double get_cutoff_radius() const = 0;

protected:

    virtual double calculate_unit_energy(const double distance) const = 0;
    virtual Vector3d calculate_unit_force(const Vector3d& vec) const = 0;

    std::shared_ptr<PairList> _get_neighbor_list() const;

    std::weak_ptr<PairList> _neighbor_list;
    std::pair<std::string, std::string> _pair;
};

std::pair<std::size_t, std::size_t> make_sorted_pair(
    const std::size_t& id0, const std::size_t& id1);

} // cgmd

#endif /* __POTENTIAL_HPP */
