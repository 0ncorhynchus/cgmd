#include "lowest_order_harmonic_bend_potential.hpp"
#include <cmath>

LowestOrderHarmonicBendPotential::LowestOrderHarmonicBendPotential(double r0, double k) :
        _r0(r0), _k(k) {
}

void LowestOrderHarmonicBendPotential::add_pair(const std::pair<std::size_t, std::size_t>& pair) {
    _pairs.push_back(pair);
}

double LowestOrderHarmonicBendPotential::calculate_energy(const Space& space) const {
    double energy(0.0);
    for (auto itr(_pairs.begin()); itr != _pairs.end(); ++itr) {
        const Vector3d vec0(space.coordinate((*itr).first));
        const Vector3d vec1(space.coordinate((*itr).second));
        const double r(norm(vec1 - vec0));
        energy += _k * pow(r-_r0, 2) / 2;
    }
    return energy;
}

vector_list LowestOrderHarmonicBendPotential::calculate_force(const Space& space) const {
    vector_list forces(space.num_beads(), Vector3d(0,0,0));
    for (auto itr(_pairs.begin()); itr != _pairs.end(); ++itr) {
        const Vector3d vec0(space.coordinate((*itr).first));
        const Vector3d vec1(space.coordinate((*itr).second));
        const Vector3d vec(vec1 - vec0);
        const double r(norm(vec));
        const Vector3d force(vec * _k * (_r0 - r) / r);
        forces.at((*itr).first) -= force;
        forces.at((*itr).second) += force;
    }
    return forces;
}
