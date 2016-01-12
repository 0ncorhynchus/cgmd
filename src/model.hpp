#ifndef __MODEL_HPP
#define __MODEL_HPP

#include "potential.hpp"
#include "bond_potential.hpp"
#include "inter_potential.hpp"
#include <vector>
#include <list>
#include <memory>

class Model {
public:
    using potential_container = std::list<std::shared_ptr<Potential> >;
    using bond_potential_contianer = std::list<std::shared_ptr<BondPotential> >;
    using inter_potential_container = std::list<std::shared_ptr<InterPotential> >;

    Model();
    Model(std::size_t size);
    void reset(const std::size_t& size);

    void set_property(const std::size_t& id, double mass, double friction);
    double get_mass(const std::size_t& id) const;
    double get_friction(const std::size_t& id) const;

    double calculate_energy(const Space& space) const;
    vector_list calculate_force(const Space& space) const;

    void add_potential(std::shared_ptr<Potential> potential);

    std::list<std::pair<std::size_t, std::size_t> > list_bonds() const;
    inter_potential_container& list_inter_potentials();

protected:
    std::vector<std::pair<double, double> > _property_list;
    bond_potential_contianer _bond_potentials;
    inter_potential_container _inter_potentials;
    potential_container _potentials;
};

#endif /* __MODEL_HPP */
