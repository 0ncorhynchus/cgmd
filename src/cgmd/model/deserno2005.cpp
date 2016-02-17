#include "deserno2005.hpp"
#include <cmath>
#include <cgmd/potential/fene_bond_potential.hpp>
#include <cgmd/potential/lowest_order_harmonic_bend_potential.hpp>
#include <cgmd/potential/weeks_chandler_anderson_potential.hpp>
#include <cgmd/potential/tails_attraction_potential.hpp>

namespace cgmd {

const std::string Deserno2005ModelFactory::HEAD = "LH";
const std::string Deserno2005ModelFactory::TAIL = "LT";

Deserno2005ModelFactory::Deserno2005ModelFactory(double sigma, double w_c, double epsilon) :
    sigma(sigma),
    w_c(w_c),
    epsilon(epsilon),
    num_lipid(1) {
}

std::shared_ptr<Model> Deserno2005ModelFactory::create() const {
    auto model = std::make_shared<Model>(num_lipid * 3);

    std::shared_ptr<FENEBondPotential> head_tail_bond(
            new FENEBondPotential(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */0.95*sigma,
                /* e = */epsilon));
    for (std::size_t i(0); i < num_lipid; ++i)
        head_tail_bond->add_bond(std::make_pair(i*3, i*3+1));
    model->add_potential(head_tail_bond);

    std::shared_ptr<FENEBondPotential> tail_tail_bond(
            new FENEBondPotential(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */sigma,
                /* e = */epsilon));
    for (std::size_t i(0); i < num_lipid; ++i)
        tail_tail_bond->add_bond(std::make_pair(i*3+1, i*3+2));
    model->add_potential(tail_tail_bond);

    std::shared_ptr<LowestOrderHarmonicBendPotential> bend(
            new LowestOrderHarmonicBendPotential(
                /* r0= */4*sigma,
                /* k = */10*epsilon/sigma/sigma));
    for (std::size_t i(0); i < num_lipid; ++i)
        bend->add_pair(std::make_pair(i*3, i*3+2));
    model->add_potential(bend);

    std::shared_ptr<WeeksChandlerAndersonPotential> head_head_replusion(
            new WeeksChandlerAndersonPotential(
                /* s= */0.95*sigma,
                /* e= */epsilon));
    head_head_replusion->set_pair("LH", "LH");
    model->add_potential(head_head_replusion);

    std::shared_ptr<WeeksChandlerAndersonPotential> head_tail_replusion(
            new WeeksChandlerAndersonPotential(
                /* s= */0.95*sigma,
                /* e= */epsilon));
    head_tail_replusion->set_pair("LH", "LT");
    model->add_potential(head_tail_replusion);

    std::shared_ptr<WeeksChandlerAndersonPotential> tail_tail_replusion(
            new WeeksChandlerAndersonPotential(
                /* s= */sigma,
                /* e= */epsilon));
    tail_tail_replusion->set_pair("LT", "LT");
    model->add_potential(tail_tail_replusion);

    std::shared_ptr<TailsAttractionPotential> tails_attraction(
            new TailsAttractionPotential(
                /* r_c= */pow(2,1.0/6.0)*sigma,
                /* w_c= */w_c,
                /* e =  */epsilon));
    tails_attraction->set_pair("LT", "LT");
    model->add_potential(tails_attraction);

    return model;
}

} // cgmd
