#include <cgmd/space.hpp>
#include <cgmd/langevin_stepper.hpp>
#include <cgmd/space_xyz_io.hpp>
#include <cgmd/model/deserno2005.hpp>

using namespace cgmd;

int main() {
    std::shared_ptr<Space> space(new Space());
    SpaceXYZReader reader("initial_structure.xyz");
    reader.load(*(space.get()));

    const std::size_t num_lipid(100);

    Deserno2005ModelFactory factory(
            /* sigma= */1.0e-10,
            /* w_c= */0.8e-10,
            /* epsilon= */5.0e-20);
    factory.num_lipid = num_lipid;
    std::shared_ptr<Model> model(factory.create());

    for (std::size_t i(0); i < num_lipid * 3; ++i)
        model->set_property(i, /* mass= */1.0e-10, /* friction= */0.2);

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
