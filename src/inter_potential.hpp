#ifndef __PAIRWISE_POTENTIAL_HPP
#define __PAIRWISE_POTENTIAL_HPP

#include "potential.hpp"
#include "pair_list.hpp"
#include <memory>
#include <string>
#include <map>

namespace cgmd {

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

} // cgmd

#endif /* __PAIRWISE_POTENTIAL_HPP */
