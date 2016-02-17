#include <cgmd/constants.hpp>
#include <cgmd/periodic_space.hpp>
#include <cgmd/langevin_stepper.hpp>
#include <cgmd/space_xyz_io.hpp>
#include <cgmd/model/deserno2005.hpp>
#include <iostream>

using namespace cgmd;

const double tau(1.0e-7);
const double epsilon(kB*300.0);
const double sigma(1.0e-10); // = 1 angstrom

int main() {
    std::shared_ptr<PeriodicSpace> space(new PeriodicSpace());
    SpaceXYZReader reader("initial_structure.xyz");
    reader.load(*(space.get()));
    space->set_lengths(25e-10, 25e-10, 25e-10);

    const std::size_t num_lipid(space->num_beads()/3);

    Deserno2005ModelFactory factory(
            /* sigma= */sigma,
            /* w_c= */1.2*sigma,
            /* epsilon= */epsilon);
    factory.num_lipid = num_lipid;
    std::shared_ptr<Model> model(factory.create());

    for (std::size_t i(0); i < num_lipid * 3; ++i)
        model->set_property(i, /* mass= */1.0e-15, /* friction= */1.0/tau);

    std::random_device rnd;
    std::mt19937 gen = std::mt19937(rnd());
    LangevinStepper stepper(space, model, gen, /* dt= */0.01*tau, /* T= */epsilon*0.8);

    SpaceXYZWriter writer("result_structure_fluid.xyz");
    writer.save(*(space.get()));
    try {
        for (int step(0); step <= 10000; ++step) {
            stepper.step();
            if (step % 100 == 0)
                writer.save(*(space.get()));
        }
    } catch (char* e) {
        std::cerr << e << std::endl;
    }
}
