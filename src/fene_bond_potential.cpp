#include "fene_bond_potential.hpp"
#include <cmath>

FENEBondPotential::FENEBondPotential(double r0, double k, double sigma, double epsilon) :
        _r0(r0), _k(k), _weeks_chandler_anderson(sigma, epsilon) {
}

void FENEBondPotential::add_bond(const std::pair<std::size_t, std::size_t>& pair) {
    _bonds.push_back(pair);
}

double FENEBondPotential::calculate_energy(const Space& space) const {
    double energy(0.0);
    for (auto itr(_bonds.begin()); itr != _bonds.end(); ++itr) {
        const Vector3d vec0(space.coordinate((*itr).first));
        const Vector3d vec1(space.coordinate((*itr).second));
        const double r(norm(vec1 - vec0));
        energy += _weeks_chandler_anderson.calculate_unit_energy(r) -
            _k * pow(_r0,2) * log(1-pow(r/_r0,2)) / 2;
    }
    return energy;
}

vector_list FENEBondPotential::calculate_force(const Space& space) const {
    vector_list forces(space.num_beads(), Vector3d(0,0,0));
    for (auto itr(_bonds.begin()); itr != _bonds.end(); ++itr) {
        const Vector3d vec0(space.coordinate((*itr).first));
        const Vector3d vec1(space.coordinate((*itr).second));
        const Vector3d vec(vec1 - vec0);
        const Vector3d force(_weeks_chandler_anderson.calculate_unit_force(vec) -
                vec * (_k / (1 - pow(norm(vec)/_r0,2))));
        forces.at((*itr).first) -= force;
        forces.at((*itr).second) += force;
    }
    return forces;
}

std::list<std::pair<std::size_t, std::size_t> > FENEBondPotential::list_bond() const {
    return _bonds;
}
