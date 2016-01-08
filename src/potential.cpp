#include "potential.hpp"

std::pair<std::size_t, std::size_t> make_sorted_pair(
    const std::size_t& id0, const std::size_t& id1) {
    if (id0 < id1)
        return std::make_pair(id0, id1);
    return std::make_pair(id1, id0);
}

