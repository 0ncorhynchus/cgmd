#include <cgmd/space.hpp>
#include <cgmd/model.hpp>
#include <cgmd/langevin_stepper.hpp>
#include <cgmd/space_xyz_io.hpp>
#include <cgmd/potential/fene_bond_potential.hpp>
#include <cgmd/potential/lowest_order_harmonic_bend_potential.hpp>

using namespace cgmd;

int main() {
    std::shared_ptr<Space> space(new Space());
    SpaceXYZReader reader("initial_structure.xyz");
    reader.load(*(space.get()));

    const std::size_t num_beads(space->num_beads());
    std::shared_ptr<Model> model(new Model(num_beads));
    model->set_property(0, 4.06e-25, 0.2*10e4);
    model->set_property(1, 4.06e-25, 0.2*10e4);
    model->set_property(2, 4.06e-25, 0.2*10e4);

    const double epsilon(1.0e-23);
    const double sigma(6.0e-10);

    std::shared_ptr<FENEBondPotential> head_tail_bond(
            new FENEBondPotential(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */0.95*sigma,
                /* e = */epsilon));
    head_tail_bond->add_bond(std::make_pair(0, 1));
    model->add_potential(head_tail_bond);

    std::shared_ptr<FENEBondPotential> tail_tail_bond(
            new FENEBondPotential(
                /* r0= */1.5*sigma,
                /* k = */30*epsilon/sigma/sigma,
                /* b = */sigma,
                /* e = */epsilon));
    tail_tail_bond->add_bond(std::make_pair(1, 2));
    model->add_potential(tail_tail_bond);

    std::shared_ptr<LowestOrderHarmonicBendPotential> bend(
            new LowestOrderHarmonicBendPotential(
                /* r0= */4*sigma,
                /* k = */10*epsilon/sigma/sigma));
    bend->add_pair(std::make_pair(0,2));
    model->add_potential(bend);

    std::random_device rnd;
    std::mt19937 gen = std::mt19937(rnd());
    LangevinStepper stepper(space, model, gen, /* dt= */1.0e-15, /* T= */300);

    SpaceXYZWriter writer("result_structure.xyz");
    for (int step(0); step <= 1000000; ++step) {
        if (step % 500 == 0)
            writer.save(*(space.get()));
        stepper.step();
    }
}
