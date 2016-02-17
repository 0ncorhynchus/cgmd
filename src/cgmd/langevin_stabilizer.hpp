#ifndef __LANGEVIN_STABILIZER_HPP
#define __LANGEVIN_STABILIZER_HPP

#include "langevin_stepper.hpp"

namespace cgmd {

class LangevinStabilizer : LangevinStepper {

public:
    LangevinStabilizer();
    LangevinStabilizer(
        std::shared_ptr<Space> space,
        std::shared_ptr<Model> model,
        std::mt19937 random_generator,
        double dt, double T);
    virtual void step();
};

} // cgmd

#endif /* __LANGEVIN_STABILIZER_HPP */
