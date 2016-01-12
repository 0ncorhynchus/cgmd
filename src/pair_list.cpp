#include "pair_list.hpp"

PairList::PairList(std::size_t size) {
    _itrs.resize(size+1, _container.begin());
}

std::size_t PairList::size() const {
    return _itrs.size()-1;
}

void PairList::clear() {
    _container.clear();
    _itrs.resize(_itrs.size(), _container.begin());
}

PairList::iterator PairList::begin(std::size_t id) const {
    return _itrs.at(id);
}

PairList::iterator PairList::end(std::size_t id) const {
    return _itrs.at(id+1);
}

void PairList::add_pair(const id_pair& pair) {
    const iterator end(_itrs.at(pair.first+1));
    const iterator itr(_container.insert(end, pair.second));
    for (int id(pair.first); id >= 0 && _itrs.at(id) == end; --id)
        _itrs.at(id) = itr;
}
