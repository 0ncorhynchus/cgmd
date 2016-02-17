#ifndef __STABILIZE_STEPPER_HPP
#define __STABILIZE_STEPPER_HPP

#include "stepper.hpp"
#include "space.hpp"
#include "model.hpp"
#include "neighbor_list_manager.hpp"
#include <memory>

namespace cgmd {

class StabilizeStepper : public Stepper {
public:
    StabilizeStepper(std::shared_ptr<Space> space, std::shared_ptr<Model> model,
            double dx);
    virtual void step();
    double dt() const;

protected:
    void initialize_parameters();
    void initialize_neighbor_list_managers();

    std::shared_ptr<Space> _space;
    std::shared_ptr<Model> _model;
    double _dx;
    double _dt;
    std::vector<double> _mass_list;
    std::list<NeighborListManager> _neighbor_list_managers;
};

} // cgmd

#endif /* __STABILIZE_STEPPER_HPP */
