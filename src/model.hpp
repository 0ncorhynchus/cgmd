#ifndef __MODEL_HPP
#define __MODEL_HPP

#include "potential.hpp"
#include <map>
#include <vector>
#include <memory>

class Model {
public:
    using potential_container = std::vector<std::shared_ptr<Potential> >;

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
    bool remove_potential(const std::size_t& i);
    const potential_container& list_potentials() const;

protected:
    bool is_in_range(const std::size_t& id) const;

protected:
    double _dt;
    std::vector<std::pair<double, double> > _property_list;
    potential_container _potentials;
};

#endif /* __MODEL_HPP */
