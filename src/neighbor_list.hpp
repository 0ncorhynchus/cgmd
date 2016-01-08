#ifndef __MY_NEIGHBOR_LIST_HPP
#define __MY_NEIGHBOR_LIST_HPP

#include <vector>
#include <list>

class NeighborList {
public:

    using iterator = std::list<std::size_t>::iterator;

    NeighborList(std::size_t size);
    iterator begin(std::size_t) const;
    iterator end(std::size_t) const;
    void add_pair(std::size_t i, std::size_t j);
    void add_distance(std::list<double> distances);

protected:
    std::list<std::size_t> _container;
    std::vector<iterator> _itrs;
    std::list<double> _distances;

};

#endif /* __MY_NEIGHBOR_LIST_HPP */
