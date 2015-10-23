#ifndef __FORCE_FIELD_HPP
#define __FORCE_FIELD_HPP

#include "bead_type.hpp"
#include "vector3d.hpp"
#include "cgspace.hpp"
#include <vector>
#include <map>

class ForceField {
    virtual double calculate_energy(const CGSpace& space) const = 0;
    virtual vector_list calculate_force(const CGSpace& space) const = 0;
};

class BondingForceField : public ForceField {
public:
    bool add_bond(const BeadType& type0, const BeadType& type1, double r, double k);
    double get_r(const BeadType& type0, const BeadType& type1) const;
    double get_k(const BeadType& type0, const BeadType& type1) const;
    virtual double calculate_energy(const CGSpace& space) const;
    virtual vector_list calculate_force(const CGSpace& space) const;

protected:
    std::map<std::pair<BeadType, BeadType>, double> _r_map;
    std::map<std::pair<BeadType, BeadType>, double> _k_map;
};

#endif /* __FORCE_FIELD_HPP */