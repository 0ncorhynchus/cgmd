#include "force_field.hpp"
#include <iostream>
#include <cmath>

std::pair<std::size_t, std::size_t> make_sorted_pair(
    const std::size_t& id0, const std::size_t& id1) {
    if (id0 < id1)
        return std::make_pair(id0, id1);
    return std::make_pair(id1, id0);
}

bool BondingForceField::add_bond(const std::size_t& id0, const std::size_t& id1,
        double r, double k) {
    auto key(make_sorted_pair(id0, id1));
    if (_map.find(key) != _map.end())
        return false;

    _map.insert(std::make_pair(key, std::make_pair(r, k)));

    return true;
}

double BondingForceField::get_r(const std::size_t& id0, const std::size_t& id1) const {
    auto key(make_sorted_pair(id0, id1));
    auto itr(_map.find(key));
    if (itr == _map.end())
        return 0.0; // Throwing the Exception is better.
    return (*itr).second.first;
}

double BondingForceField::get_k(const std::size_t& id0, const std::size_t& id1) const {
    auto key(make_sorted_pair(id0, id1));
    auto itr(_map.find(key));
    if (itr == _map.end())
        return 0.0; // Throwing the Exception is better.
    return (*itr).second.second;
}

double BondingForceField::calculate_energy(const CGSpace& space) const {
    double energy(0);

    for (auto itr(_map.begin()); itr != _map.end(); ++itr) {
        const std::size_t former((*itr).first.first),
                          latter((*itr).first.second);
        if (former < 0 || former >= space.num_beads() ||
                latter < 0 || latter >= space.num_beads())
            continue;
        const double r((*itr).second.first);
        const double k((*itr).second.second);
        const double R(norm(space.coordinate(former) - space.coordinate(latter)));
        energy += k * pow(R - r, 2.0);
    }

    return energy;
}

vector_list BondingForceField::calculate_force(const CGSpace& space) const {
    vector_list force_list(space.num_beads(), Vector3d(0,0,0));

    for (auto itr(_map.begin()); itr != _map.end(); ++itr) {
        const std::size_t former((*itr).first.first),
                          latter((*itr).first.second);
        if (former < 0 || former >= space.num_beads() ||
                latter < 0 || latter >= space.num_beads())
            continue;
        const double r((*itr).second.first);
        const double k((*itr).second.second);
        const Vector3d vec(space.coordinate(former) - space.coordinate(latter));
        const double R(norm(vec));
        const double strength(2.0*k*(R-r)/R);
        force_list.at(former) -= vec * strength;
        force_list.at(latter) += vec * strength;
    }

    return force_list;
}
