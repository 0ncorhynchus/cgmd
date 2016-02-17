#include "langevin_stabilizer.hpp"

namespace cgmd {

LangevinStabilizer::LangevinStabilizer() : LangevinStepper() {
}

LangevinStabilizer::LangevinStabilizer(std::shared_ptr<Space> space,
    std::shared_ptr<Model> model, std::mt19937 random_generator, double dt, double T) :
    LangevinStepper(space, model, random_generator, dt, T) {
}

void LangevinStabilizer::step() {
    LangevinStepper::step();
    for (std::size_t i(0); i < _space->num_beads(); ++i)
        _space->velocity(i) = Vector3d(0,0,0);
}

} // cgmd
