#ifndef __MY_PAIR_LIST_HPP
#define __MY_PAIR_LIST_HPP

#include <vector>
#include <list>

using id_pair = std::pair<std::size_t, std::size_t>;

class PairList {
public:

    using iterator = std::list<std::size_t>::iterator;

    PairList(std::size_t size);
    std::size_t size() const;
    void clear();
    iterator begin(std::size_t i) const;
    iterator end(std::size_t i) const;
    void add_pair(const id_pair& pair);

protected:
    std::vector<iterator> _itrs;
    std::list<std::size_t> _container;

};

#endif /* __MY_NEIGHBOR_LIST_HPP */
