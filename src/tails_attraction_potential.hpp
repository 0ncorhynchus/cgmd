#ifndef __TAILS_ATTRACTION_POTENTIAL_HPP
#define __TAILS_ATTRACTION_POTENTIAL_HPP

#include "inter_potential.hpp"

class TailsAttractionPotential : public InterPotential {
public:
    TailsAttractionPotential(double inner_radius ,double cutoff_width, double epsilon);
    double get_cutoff_radius() const;

protected:
    double calculate_unit_energy(const double distance) const;
    Vector3d calculate_unit_force(const Vector3d& vec) const;

    const double _r_c;
    const double _w_c;
    const double _minus_epsilon;
};

#endif /* __TAILS_ATTRACTION_POTENTIAL_HPP */
