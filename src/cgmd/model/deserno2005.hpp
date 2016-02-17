#ifndef __CGMD_DESERNO2005_HPP
#define __CGMD_DESERNO2005_HPP

#include <cgmd/model_factory.hpp>
#include <string>

namespace cgmd {

class Deserno2005ModelFactory : public ModelFactory {
public:

    const static std::string HEAD;
    const static std::string TAIL;

    Deserno2005ModelFactory(double sigma, double w_c, double epsilon);
    std::shared_ptr<Model> create() const;

    const double sigma;
    const double w_c;
    const double epsilon;
    std::size_t num_lipid;
};

} // cgmd

#endif /* __CGMD_DESERNO2005_HPP */
