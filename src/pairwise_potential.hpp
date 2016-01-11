#ifndef __PAIRWISE_POTENTIAL_HPP
#define __PAIRWISE_POTENTIAL_HPP

#include "potential.hpp"
#include "neighbor_list.hpp"
#include <memory>
#include <string>
#include <map>

class PairwisePotential : public Potential{
public:
    virtual double calculate_energy(const Space& space) const {
        double energy(0);
        if(std::shared_ptr<NeighborList> neighbor_list = get_neighbor_list()) {
            const std::size_t size(neighbor_list->size());
            for (std::size_t i(0); i < size; ++i) {
                const Vector3d coord(space.coordinate(i));
                for (auto itr(neighbor_list->begin(i)); itr != neighbor_list->end(i); ++itr) {
                    energy += calculate_unit_energy(norm(space.coordinate(*itr) - coord));
                }
            }
        } else {
            const std::size_t num_beads(space.num_beads());
            for (std::size_t i(0); i < num_beads-1; ++i) {
                const std::string symbol0(space.symbol(i));
                if (symbol0 != _pair.first && symbol0 != _pair.second)
                    continue;
                const Vector3d coord(space.coordinate(i));
                for (std::size_t j(i+1); j < num_beads; ++j) {
                    if (is_valid_pair(symbol0, space.symbol(j)))
                        energy += calculate_unit_energy(norm(space.coordinate(j) - coord));
                }
            }
        }
        return energy;
    }

    virtual vector_list calculate_force(const Space& space) const {
        const std::size_t num_beads(space.num_beads());
        vector_list forces(num_beads, Vector3d(0,0,0));
        if(std::shared_ptr<NeighborList> neighbor_list = get_neighbor_list()) {
            const std::size_t size(neighbor_list->size());
            for (std::size_t i(0); i < size; ++i) {
                const Vector3d coord(space.coordinate(i));
                for (auto itr(neighbor_list->begin(i)); itr != neighbor_list->end(i); ++itr) {
                    const Vector3d force(calculate_unit_force(space.coordinate(*itr) - coord));
                    forces.at(i) -= force;
                    forces.at(*itr) += force;
                }
            }
        } else {
            for (std::size_t i(0); i < num_beads-1; ++i) {
                const std::string symbol0(space.symbol(i));
                if (symbol0 != _pair.first && symbol0 != _pair.second)
                    continue;
                const Vector3d coord(space.coordinate(i));
                for (std::size_t j(i+1); j < num_beads; ++j) {
                    if (is_valid_pair(symbol0, space.symbol(j))) {
                        const Vector3d force(calculate_unit_force(space.coordinate(j) - coord));
                        forces.at(i) -= force;
                        forces.at(j) += force;
                    }
                }
            }
        }
        return forces;
    }

    void set_neighbor_list(std::shared_ptr<NeighborList> neighbor_list) {
        _neighbor_list = neighbor_list;
    }

    void set_pair(std::string serial0, std::string serial1) {
        _pair = std::make_pair(serial0, serial1);
    }

    std::pair<std::string, std::string> get_pair() const {
        return _pair;
    }

    bool is_valid_pair(std::string symbol0, std::string symbol1) const {
        return (_pair.first == "" && _pair.second == "") ||
            (symbol0 == _pair.first && symbol1 == _pair.second) ||
            (symbol0 == _pair.second && symbol1 == _pair.first);
    }

protected:

    virtual double calculate_unit_energy(const double distance) const = 0;
    virtual Vector3d calculate_unit_force(const Vector3d& vec) const = 0;

    std::shared_ptr<NeighborList> get_neighbor_list() const {
        return _neighbor_list.lock();
    }

    std::weak_ptr<NeighborList> _neighbor_list;
    std::pair<std::string, std::string> _pair;
};

#endif /* __PAIRWISE_POTENTIAL_HPP */
