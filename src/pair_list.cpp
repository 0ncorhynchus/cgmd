#include "pair_list.hpp"

PairList::PairList(std::size_t size) {
    _container.clear();
    _itrs.resize(size, _container.begin());
}

std::size_t PairList::size() const {
    return _itrs.size();
}

PairList::iterator PairList::begin(std::size_t id) const {
    return _itrs.at(id);
}

PairList::iterator PairList::end(std::size_t id) const {
    return _itrs.at(id+1);
}

void PairList::add_pair(std::size_t i, std::size_t j) {
    const iterator end(_itrs.at(i+1));
    const iterator itr(_container.insert(end, j));
    for (int id(i); id >= 0 && _itrs.at(id) == end; --id)
        _itrs.at(id) = itr;
}
