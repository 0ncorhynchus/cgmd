#include "space_xyz_io.hpp"
#include <fstream>
#include <iomanip>

SpaceXYZWriter::SpaceXYZWriter(const std::string& fname) : _fname(fname) {}

void SpaceXYZWriter::save(const Space& space) {
    std::ofstream ofs(_fname);
    const std::size_t num(space.num_beads());
    ofs << num << std::endl; // # of beads
    ofs << "Generated by a program" << std::endl; // Some comments
    for (int i(0); i < num; ++i) {
        const std::string symbol(space.symbol(i));
        const Vector3d coord(space.coordinate(i));
        ofs << std::setw(5) << std::left << symbol
            << " " << std::setw(15) << std::right << std::fixed << std::setprecision(6) << coord.x
            << " " << std::setw(15) << std::right << std::fixed << std::setprecision(6) << coord.y
            << " " << std::setw(15) << std::right << std::fixed << std::setprecision(6) << coord.z
            << std::endl;
    }
}
