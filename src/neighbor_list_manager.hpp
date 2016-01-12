#ifndef __NEIGHBOR_LIST_MANAGER_HPP
#define __NEIGHBOR_LIST_MANAGER_HPP

#include "pair_list.hpp"
#include "space.hpp"
#include <string>
#include <map>
#include <memory>
#include <list>

/*
 * The instance of this will be initialized by Stepper
 */
class NeighborListManager {
public:
    NeighborListManager(std::size_t num_beads, double r_c, double r_l, double dt);
    void update(const Space& space);
    bool to_update(double t) const;
    void add_candidate(const id_pair& candidate);
    void add_displacements(const std::list<double>& displacements);
    std::shared_ptr<PairList> get_neighbor_list();

protected:
    const double _threshold_radius;
    const double _list_radius;
    const double _dt_update;
    double _next_time;

    std::shared_ptr<PairList> _neighbor_list;
    std::list<double> _displacements;
    std::list<id_pair> _candidates;
    bool _update_flg;
};

#endif /* __NEIGHBOR_LIST_MANAGER_HPP */
