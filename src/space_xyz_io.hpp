#ifndef __SPACE_XYZ_IO_HPP
#define __SPACE_XYZ_IO_HPP

#include "space_io.hpp"
#include <string>

namespace cgmd {

class SpaceXYZWriter : public SpaceWriter {
public:
    SpaceXYZWriter(const std::string& fname);
    virtual void save(const Space& space) const;

protected:
    const std::string _fname;
};

class SpaceXYZReader : public SpaceReader {
public:
    SpaceXYZReader(const std::string& fname);
    virtual void load(Space& space) const;

protected:
    const std::string _fname;
};

} // cgmd

#endif /* __SPACE_XYZ_IO_HPP */
