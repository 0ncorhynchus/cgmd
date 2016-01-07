#include "neighbor_list.hpp"

NeighborList::NeighborList(std::size_t size) {
    _itrs.resize(size+1, _container.begin());
}

NeighborList::iterator NeighborList::begin(std::size_t id) const {
    return _itrs.at(id);
}

NeighborList::iterator NeighborList::end(std::size_t id) const {
    return _itrs.at(id+1);
}

void NeighborList::add_pair(std::size_t i, std::size_t j) {
    const iterator end(_itrs.at(i+1));
    const iterator itr(_container.insert(end, j));
    for (int id(i); id >= 0 && _itrs.at(id) == end; --id)
        _itrs.at(id) = itr;
}
