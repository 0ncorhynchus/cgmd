#ifndef __CGSPACE_HPP
#define __CGSPACE_HPP

#include <vector>
#include <map>
#include <set>
#include "vector3d.hpp"

namespace cgmd {

class Space {
public:

    Space();
    Space(const std::size_t& size);
    void reset(const std::size_t& size);

    std::string& symbol(std::size_t index);
    const std::string& symbol(std::size_t index) const;

    Vector3d& coordinate(std::size_t index);
    const Vector3d& coordinate(std::size_t index) const;

    Vector3d& velocity(std::size_t index);
    const Vector3d& velocity(std::size_t index) const;

    virtual Vector3d direct(std::size_t i, std::size_t j) const;
    virtual double distance(std::size_t i, std::size_t j) const;

    std::size_t num_beads() const {
        return _coordinates.size();
    }
    double t() const {
        return _t;
    }
    void set_t(double t) {
        _t = t;
    }

protected:
    std::vector<std::string> _symbols;
    vector_list _coordinates;
    vector_list _velocities;
    double _t;
};

} // cgmd

#endif /* __CGSPACE_HPP*/
