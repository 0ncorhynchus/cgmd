#include "neighbor_list_manager.hpp"
#include <algorithm>

NeighborListManager::NeighborListManager(std::size_t num_beads, double r_c, double r_l, double dt) :
        _threshold_radius(r_l - r_c),
        _list_radius(r_l),
        _dt_update(dt),
        _neighbor_list(std::make_shared<PairList>(num_beads-1)),
        _displacements(num_beads, 0.0) {
    _next_time = _dt_update;
    _update_flg = false;
}

void NeighborListManager::update(const Space& space) {
    _neighbor_list->clear();
    for (auto itr(_candidates.begin()); itr != _candidates.end(); ++itr) {
        const double r(norm(space.coordinate((*itr).first)-space.coordinate((*itr).second)));
        if (r <= _list_radius)
            _neighbor_list->add_pair(*itr);
    }
    _displacements.resize(_displacements.size(), 0.0);
    _update_flg = false;
}

bool NeighborListManager::to_update(double t) const {
    return t >= _next_time || _update_flg;
}

void NeighborListManager::add_candidate(const id_pair& candidate) {
    _candidates.push_back(candidate);
}

void NeighborListManager::add_displacements(const std::list<double>& displacements) {
    double largest1(0.0), largest2(0.0);
    auto add_itr(displacements.begin());
    auto itr(_displacements.begin());
    while (add_itr != displacements.end() && itr != _displacements.end()) {
        *itr += *add_itr;

        const double displacement(*itr);
        if (displacement >= largest1) {
            largest2 = largest1;
            largest1 = displacement;
        } else if (displacement >= largest2) {
            largest2 = displacement;
        }

        ++itr;
        ++add_itr;
    }

    if (largest1 + largest2 > _threshold_radius)
        _update_flg = true;
}

std::shared_ptr<PairList> NeighborListManager::get_neighbor_list() {
    return _neighbor_list;
}
