#ifndef __PAIRWISE_POTENTIAL_HPP
#define __PAIRWISE_POTENTIAL_HPP

#include "potential.hpp"
#include "neighbor_list.hpp"
#include <memory>

class PairwisePotential : public Potential{
public:
    virtual double calculate_energy(const Space& space) const {
        double energy(0);
        const std::size_t num_beads(space.num_beads());
        if(std::shared_ptr<NeighborList> neighbor_list = get_neighbor_list()) {
            for (std::size_t i(0); i < num_beads-1; ++i) {
                const Vector3d coord(space.coordinate(i));
                for (auto itr(neighbor_list->begin(i)); itr != neighbor_list->end(i); ++itr) {
                    energy += calculate_unit_energy(norm(space.coordinate(*itr) - coord));
                }
            }
        } else {
            for (std::size_t i(0); i < num_beads-1; ++i) {
                const Vector3d coord(space.coordinate(i));
                for (std::size_t j(i+1); j < num_beads; ++j) {
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
            for (std::size_t i(0); i < num_beads-1; ++i) {
                const Vector3d coord(space.coordinate(i));
                for (auto itr(neighbor_list->begin(i)); itr != neighbor_list->end(i); ++itr) {
                    const Vector3d force(calculate_unit_force(space.coordinate(*itr) - coord));
                    forces.at(i) -= force;
                    forces.at(*itr) += force;
                }
            }
        } else {
            for (std::size_t i(0); i < num_beads-1; ++i) {
                const Vector3d coord(space.coordinate(i));
                for (std::size_t j(i+1); j < num_beads; ++j) {
                    const Vector3d force(calculate_unit_force(space.coordinate(j) - coord));
                    forces.at(i) -= force;
                    forces.at(j) += force;
                }
            }
        }
        return forces;
    }

    void set_neighbor_list(std::shared_ptr<NeighborList> neighbor_list) {
        _neighbor_list = neighbor_list;
    }

protected:

    virtual double calculate_unit_energy(const double distance) const = 0;
    virtual Vector3d calculate_unit_force(const Vector3d& vec) const = 0;

    std::shared_ptr<NeighborList> get_neighbor_list() const {
        return _neighbor_list.lock();
    }

    std::weak_ptr<NeighborList> _neighbor_list;
};

#endif /* __PAIRWISE_POTENTIAL_HPP */
