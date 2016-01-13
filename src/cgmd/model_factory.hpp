#ifndef __CGMD_MODEL_FACTORY_HPP
#define __CGMD_MODEL_FACTORY_HPP

#include "model.hpp"
#include <memory>

namespace cgmd {

class ModelFactory {
public:
    virtual std::shared_ptr<Model> create() const = 0;
};

} // cgmd

#endif /* __CGMD_MODEL_FACTORY_HPP */
