#ifndef __STEPPER_HPP
#define __STEPPER_HPP

namespace cgmd {

class Stepper {
public:
    virtual void step() = 0;
};

} // cgmd

#endif /* __STEPPER_HPP */
