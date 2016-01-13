#include <space.hpp>
#include <model.hpp>
#include <langevin_stepper.hpp>
#include <space_xyz_io.hpp>
#include <fene_bond_potential.hpp>
#include <lowest_order_harmonic_bend_potential.hpp>

using namespace cgmd;

int main() {
    std::shared_ptr<Space> space(std::make_shared<Space>());
    SpaceXYZReader reader("initial_structure.xyz");
    reader.load(*(space.get()));

    const std::size_t num_beads(space->num_beads());
    std::shared_ptr<Model> model(std::make_shared<Model>(num_beads));
    model->set_property(0, 1.0e-10, 0.2);
    model->set_property(1, 1.0e-10, 0.2);
    model->set_property(2, 1.0e-10, 0.2);

    const double epsilon(1.0e-20);
    const double sigma(1.0e-10);

    std::shared_ptr<FENEBondPotential> head_tail_bond(
            std::make_shared<FENEBondPotential>(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */0.95*sigma,
                /* e = */epsilon));
    head_tail_bond->add_bond(std::make_pair(0, 1));
    model->add_potential(head_tail_bond);

    std::shared_ptr<FENEBondPotential> tail_tail_bond(
            std::make_shared<FENEBondPotential>(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */sigma,
                /* e = */epsilon));
    tail_tail_bond->add_bond(std::make_pair(1, 2));
    model->add_potential(tail_tail_bond);

    std::shared_ptr<LowestOrderHarmonicBendPotential> bend(
            std::make_shared<LowestOrderHarmonicBendPotential>(
                /* r0= */4*sigma,
                /* k = */10*epsilon/sigma/sigma));
    bend->add_pair(std::make_pair(0,2));
    model->add_potential(bend);

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
