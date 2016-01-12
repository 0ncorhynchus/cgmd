#ifndef __PAIRWISE_POTENTIAL_HPP
#define __PAIRWISE_POTENTIAL_HPP

#include "inter_potential.hpp"
#include "neighbor_list.hpp"
#include <memory>
#include <string>
#include <map>

class PairwisePotential : public InterPotential{
public:
    double calculate_energy(const Space& space) const;
    vector_list calculate_force(const Space& space) const;

    void set_neighbor_list(std::shared_ptr<NeighborList> neighbor_list);
    void set_pair(std::string symbol0, std::string symbol1);
    std::pair<std::string, std::string> get_pair() const;

    bool is_valid_pair(std::string symbol0, std::string symbol1) const {
        return (_pair.first == "" && _pair.second == "") ||
            (symbol0 == _pair.first && symbol1 == _pair.second) ||
            (symbol0 == _pair.second && symbol1 == _pair.first);
    }

protected:

    virtual double calculate_unit_energy(const double distance) const = 0;
    virtual Vector3d calculate_unit_force(const Vector3d& vec) const = 0;

    std::shared_ptr<NeighborList> _get_neighbor_list() const;

    std::weak_ptr<NeighborList> _neighbor_list;
    std::pair<std::string, std::string> _pair;
};

#endif /* __PAIRWISE_POTENTIAL_HPP */
