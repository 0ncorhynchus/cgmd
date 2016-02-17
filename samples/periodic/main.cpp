#include <cgmd/constants.hpp>
#include <cgmd/periodic_space.hpp>
#include <cgmd/langevin_stepper.hpp>
#include <cgmd/space_xyz_io.hpp>
#include <cgmd/model/deserno2005.hpp>

using namespace cgmd;

int main() {
    const std::size_t num_lipid(100);
    const double T(300.0);
    const double tau(1.0e-7);
    const double sigma(1.0e-10);

    std::shared_ptr<PeriodicSpace> space(new PeriodicSpace());
    SpaceXYZReader reader("initial_structure.xyz");
    reader.load(*(space.get()));
    space->set_lengths(12e-10, 12e-10, 50e-10);

    Deserno2005ModelFactory factory(
            /* sigma= */sigma,
            /* w_c= */0.8*sigma,
            /* epsilon= */2.0*kB*T);
    factory.num_lipid = num_lipid;
    std::shared_ptr<Model> model(factory.create());

    for (std::size_t i(0); i < num_lipid * 3; ++i)
        model->set_property(i, /* mass= */4.06e-25, /* friction= */1.0/tau);

    std::random_device rnd;
    std::mt19937 gen = std::mt19937(rnd());
    LangevinStepper stepper(space, model, gen, /* dt= */0.01*tau, /* T= */T);

    SpaceXYZWriter writer("result_structure.xyz");
    for (int step(0); step <= 4000; ++step) {
        if (step % 100 == 0)
            writer.save(*(space.get()));
        stepper.step();
    }
}
