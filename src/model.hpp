#ifndef __MODEL_HPP
#define __MODEL_HPP

#include "potential.hpp"
#include "inter_potential.hpp"
#include "intra_potential.hpp"
#include <vector>
#include <list>
#include <memory>

class Model {
public:
    using potential_container = std::list<std::shared_ptr<Potential> >;
    using iterator = potential_container::iterator;

    Model();
    Model(std::size_t size);
    void set_dt(double dt);
    void reset(const std::size_t& size);
    void set_property(const std::size_t& id, double mass, double friction);
    double get_dt() const;
    double get_mass(const std::size_t& id) const;
    double get_friction(const std::size_t& id) const;
    vector_list calculate_force(std::shared_ptr<Space> space) const;
    double calculate_energy(std::shared_ptr<Space> space) const;

    void add_potential(std::shared_ptr<Potential> potential);
    void add_potential(std::shared_ptr<InterPotential> potential);
    const potential_container& list_potentials() const;

protected:
    double _dt;
    std::vector<std::pair<double, double> > _property_list;
    potential_container _potentials;
    iterator _bonding_itr;
    iterator _intra_itr;
    iterator _inter_itr;
};

#endif /* __MODEL_HPP */
