#include <space.hpp>
#include <model.hpp>
#include <langevin_stepper.hpp>
#include <space_xyz_io.hpp>
#include <fene_bond_potential.hpp>
#include <lowest_order_harmonic_bend_potential.hpp>
#include <weeks_chandler_anderson_potential.hpp>
#include <tails_attraction_potential.hpp>

using namespace cgmd;

int main() {
    std::shared_ptr<Space> space(std::make_shared<Space>());
    SpaceXYZReader reader("initial_structure.xyz");
    reader.load(*(space.get()));

    const std::size_t num_lipid(9);
    std::shared_ptr<Model> model(std::make_shared<Model>(num_lipid * 3));
    for (std::size_t i(0); i < num_lipid * 3; ++i)
        model->set_property(i, 1.0e-10, 0.2);

    const double epsilon(1.0e-20);
    const double sigma(1.0e-10);

    std::shared_ptr<FENEBondPotential> head_tail_bond(
            std::make_shared<FENEBondPotential>(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */0.95*sigma,
                /* e = */epsilon));
    for (std::size_t i(0); i < num_lipid; ++i)
        head_tail_bond->add_bond(std::make_pair(i*3, i*3+1));
    model->add_potential(head_tail_bond);

    std::shared_ptr<FENEBondPotential> tail_tail_bond(
            std::make_shared<FENEBondPotential>(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */sigma,
                /* e = */epsilon));
    for (std::size_t i(0); i < num_lipid; ++i)
        tail_tail_bond->add_bond(std::make_pair(i*3+1, i*3+2));
    model->add_potential(tail_tail_bond);

    std::shared_ptr<LowestOrderHarmonicBendPotential> bend(
            std::make_shared<LowestOrderHarmonicBendPotential>(
                /* r0= */4*sigma,
                /* k = */10*epsilon/sigma/sigma));
    for (std::size_t i(0); i < num_lipid; ++i)
        bend->add_pair(std::make_pair(i*3, i*3+2));
    model->add_potential(bend);

    std::shared_ptr<WeeksChandlerAndersonPotential> head_head_replusion(
            std::make_shared<WeeksChandlerAndersonPotential>(
                /* s= */0.95*sigma,
                /* e= */epsilon));
    head_head_replusion->set_pair("LH", "LH");
    model->add_potential(head_head_replusion);

    std::shared_ptr<WeeksChandlerAndersonPotential> head_tail_replusion(
            std::make_shared<WeeksChandlerAndersonPotential>(
                /* s= */0.95*sigma,
                /* e= */epsilon));
    head_tail_replusion->set_pair("LH", "LT");
    model->add_potential(head_tail_replusion);

    std::shared_ptr<WeeksChandlerAndersonPotential> tail_tail_replusion(
            std::make_shared<WeeksChandlerAndersonPotential>(
                /* s= */sigma,
                /* e= */epsilon));
    tail_tail_replusion->set_pair("LT", "LT");
    model->add_potential(tail_tail_replusion);

    std::shared_ptr<TailsAttractionPotential> tails_attraction(
            std::make_shared<TailsAttractionPotential>(
                /* r_c= */pow(2,1.0/6.0)*sigma,
                /* w_c= */0.8*sigma,
                /* e =  */epsilon));
    tails_attraction->set_pair("LT", "LT");
    model->add_potential(tails_attraction);

    std::random_device rnd;
    std::mt19937 gen = std::mt19937(rnd());
    LangevinStepper stepper(space, model, gen, /* dt= */1.0e-9, /* T= */300);

    SpaceXYZWriter writer("result_structure.xyz");
    for (int step(0); step <= 1000000; ++step) {
        if (step % 500 == 0)
            writer.save(*(space.get()));
        stepper.step();
    }
}
