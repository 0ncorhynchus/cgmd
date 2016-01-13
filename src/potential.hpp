#ifndef __FORCE_FIELD_HPP
#define __FORCE_FIELD_HPP

#include "vector3d.hpp"
#include "space.hpp"
#include <map>

namespace cgmd {

class Potential {
public:
    virtual double calculate_energy(const Space& space) const = 0;
    virtual vector_list calculate_force(const Space& space) const = 0;
};

std::pair<std::size_t, std::size_t> make_sorted_pair(
    const std::size_t& id0, const std::size_t& id1);

} // cgmd

#endif /* __FORCE_FIELD_HPP */
