#ifndef __CGMD_PERIODIC_SPACE_HPP
#define __CGMD_PERIODIC_SPACE_HPP

#include "space.hpp"

namespace cgmd {

class PeriodicSpace : public Space {
public:

    PeriodicSpace();
    PeriodicSpace(const std::size_t size, double X, double Y, double Z);

    void set_lengths(double X, double Y, double Z);
    void initialize();

    void move(std::size_t index, const Vector3d& direction);
    Vector3d direct(std::size_t i, std::size_t j) const;

protected:

    void adjust(std::size_t index);

    double _x, _y, _z;
};

} // cgmd

#endif /* __CGMD_PERIODIC_SPACE_HPP */
