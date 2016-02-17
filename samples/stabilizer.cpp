#include <cgmd/constants.hpp>
#include <cgmd/stabilize_stepper.hpp>
#include <cgmd/periodic_space.hpp>
#include <cgmd/space_xyz_io.hpp>
#include <cgmd/model/deserno2005.hpp>
#include <iostream>

using namespace cgmd;

const double T(300.0);
const double tau(1.0e-7);
const double sigma(1.0e-10); // = 1 angstrom

int main(int argc, char** argv) {
    std::shared_ptr<PeriodicSpace> space(new PeriodicSpace());
    SpaceXYZReader reader(argv[1]);
    reader.load(*(space.get()));
    space->set_lengths(25e-10, 25e-10, 25e-10);
    const std::size_t num_lipid(space->num_beads()/3);

    Deserno2005ModelFactory factory(
            /* sigma= */sigma,
            /* w_c= */1.2*sigma,
            /* epsilon= */kB*T/0.7);
    factory.num_lipid = num_lipid;
    std::shared_ptr<Model> model(factory.create());

    for (std::size_t i(0); i < num_lipid * 3; ++i)
        model->set_property(i, /* mass= */1.0e-15, /* friction= */1.0/tau);

    StabilizeStepper stepper(space, model, /* dx= */0.05*1.0e-10);

    while (stepper.dt() < 0.01*tau) {
        stepper.step();
    }
    std::cout << space->t() << ": " << stepper.dt() << std::endl;
    SpaceXYZWriter writer(argv[2]);
    writer.save(*(space.get()));
}
