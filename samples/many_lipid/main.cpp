#include <cgmd/space.hpp>
#include <cgmd/model.hpp>
#include <cgmd/langevin_stepper.hpp>
#include <cgmd/space_xyz_io.hpp>
#include <cgmd/potential/fene_bond_potential.hpp>
#include <cgmd/potential/lowest_order_harmonic_bend_potential.hpp>
#include <cgmd/potential/weeks_chandler_anderson_potential.hpp>
#include <cgmd/potential/tails_attraction_potential.hpp>

using namespace cgmd;

int main() {
    std::shared_ptr<Space> space(new Space());
    SpaceXYZReader reader("initial_structure.xyz");
    reader.load(*(space.get()));

    const std::size_t num_lipid(100);
    std::shared_ptr<Model> model(new Model(num_lipid * 3));
    for (std::size_t i(0); i < num_lipid * 3; ++i)
        model->set_property(i, 1.0e-10, 0.2);

    const double epsilon(5.0e-20);
    const double sigma(1.0e-10);

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
                /* w_c= */0.8*sigma,
                /* e =  */epsilon));
    tails_attraction->set_pair("LT", "LT");
    model->add_potential(tails_attraction);

    std::random_device rnd;
    std::mt19937 gen = std::mt19937(rnd());
    LangevinStepper stepper(space, model, gen, /* dt= */1.0e-9, /* T= */300);

    SpaceXYZWriter writer("result_structure.xyz");
    for (int step(0); step <= 100000; ++step) {
        if (step % 500 == 0)
            writer.save(*(space.get()));
        stepper.step();
    }
}
