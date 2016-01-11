#ifndef __MY_NEIGHBOR_LIST_HPP
#define __MY_NEIGHBOR_LIST_HPP

#include <vector>
#include <list>

class NeighborList {
public:

    using iterator = std::list<std::size_t>::iterator;

    NeighborList(std::size_t size);
    std::size_t size() const;
    iterator begin(std::size_t i) const;
    iterator end(std::size_t i) const;
    void add_pair(std::size_t i, std::size_t j);

protected:
    std::vector<iterator> _itrs;
    std::list<std::size_t> _container;

};

#endif /* __MY_NEIGHBOR_LIST_HPP */
