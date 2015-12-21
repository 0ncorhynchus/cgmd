#ifndef __CGSPACE_HPP
#define __CGSPACE_HPP

#include <vector>
#include <map>
#include <set>
#include "vector3d.hpp"

class CGSpace {
public:

    CGSpace();
    CGSpace(const std::size_t& size);
    void reset(const std::size_t& size);
    Vector3d& coordinate(std::size_t index);
    const Vector3d& coordinate(std::size_t index) const;
    Vector3d& velocity(std::size_t index);
    const Vector3d& velocity(std::size_t index) const;
    std::size_t num_beads() const;
    double& t();
    const double& t() const;

protected:
    vector_list _coordinates;
    vector_list _velocities;
    double _t;
};

#endif /* __CGSPACE_HPP*/
