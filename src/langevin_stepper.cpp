#include "langevin_stepper.hpp"
#include "constants.hpp"
#include <memory>
#include <math.h>

LangevinStepper::LangevinStepper() : _dt(0), _T(0) {
}

LangevinStepper::LangevinStepper(const LangevinStepper& stepper)
        : _dt(stepper._dt), _T(stepper._T) {
#define COPY_VECTOR(VAR) \
    copy(stepper.VAR.begin(), stepper.VAR.end(), back_inserter(VAR))
    COPY_VECTOR(_acceleration_list);
    COPY_VECTOR(_deviation);
    COPY_VECTOR(_const_term2);
    COPY_VECTOR(_const_term3);
    COPY_VECTOR(_const_term4);
    COPY_VECTOR(_mass_list);
#undef COPY_VECTOR
}

LangevinStepper::LangevinStepper(std::shared_ptr<Space> space,
    std::shared_ptr<Model> model, std::mt19937 random_generator, double dt, double T) :
    _space(space), _model(model), _dist(0,1), _gen(random_generator), _dt(dt), _T(T) {
    const std::size_t num_beads(_space->num_beads());

    _acceleration_list = vector_list(num_beads, Vector3d(0,0,0));
    _deviation = std::vector<double>(num_beads);
    _const_term2 = std::vector<double>(num_beads);
    _const_term3 = std::vector<double>(num_beads);
    _const_term4 = std::vector<double>(num_beads);
    _mass_list = std::vector<double>(num_beads);

    for (std::size_t id(0); id < num_beads; ++id) {
        const double friction(_model->get_friction(id));
        const double mass(_model->get_mass(id));
        _deviation[id] = sqrt(2*friction*kB*_T/mass/_dt);
        _const_term2[id] = (1-friction*_dt/2)*(1-friction*_dt/2+pow(friction*dt/2,2));
        _const_term3[id] = _dt/2*(1-friction*_dt/2);
        _const_term4[id] = _dt*(1-friction*_dt/2);
        _mass_list[id] = mass;
    }
}

void LangevinStepper::step() {
    const std::size_t num_beads(_space->num_beads());

    // Update Coordinate
    for (std::size_t i(0); i < num_beads; ++i)
        _space->coordinate(i) += _space->velocity(i) * _const_term4.at(i)
            + _acceleration_list.at(i) * _dt*_dt/2;

    // Update Force
    vector_list force_list(num_beads, Vector3d(0,0,0));
    const Model::potential_container& potentials(_model->list_potentials());
    for (auto itr(potentials.begin()); itr != potentials.end(); ++itr)
        force_list += (*itr)->calculate_force(*(_space.get()));

    vector_list new_acceleration(num_beads, Vector3d(0,0,0));
    for (std::size_t i(0); i < num_beads; ++i) {
        new_acceleration[i] = force_list.at(i) / _mass_list.at(i)
            + get_unit_random_force() * _deviation.at(i);
    }

    // Update Velocity
    for (std::size_t i(0); i < num_beads; ++i)
        _space->velocity(i) = _space->velocity(i) * _const_term2.at(i)
            + (_acceleration_list.at(i) + new_acceleration.at(i)) * _const_term3.at(i);

    _space->set_t(_space->t() + _dt);
    _acceleration_list = new_acceleration;
}

double LangevinStepper::get_unit_white_noise() {
    return _dist(_gen);
}

Vector3d LangevinStepper::get_unit_random_force() {
    const double r(get_unit_white_noise());
    const double t(get_unit_white_noise() * M_PI);
    const double p(get_unit_white_noise() * M_PI * 2);
    return Vector3d(
            r * sin(t) * cos(p),
            r * sin(t) * sin(p),
            r * cos(t));
}
