#include <gtest/gtest.h>
#include <memory>
#include <random>
#include <cgmd/space.hpp>
#include <cgmd/model.hpp>
#include <cgmd/langevin_stepper.hpp>

using namespace cgmd;

namespace {

class LangevinStepperTest : public ::testing::Test {
protected:
    LangevinStepperTest() :
        rnd(), gen(rnd()),
        model(new Model()),
        space(new Space()),
        stepper(space, model, gen, /* dt= */0.2, /* T= */200) {
    }

    // virtual void SetUp() {}
    // virtual void TearDown() {}

    std::random_device rnd;
    std::mt19937 gen;
    std::shared_ptr<Model> model;
    std::shared_ptr<Space> space;
    LangevinStepper stepper;
};

TEST_F(LangevinStepperTest, Step) {
    stepper.step();
    EXPECT_EQ(0.2, space->t());
}

TEST_F(LangevinStepperTest, Neighbor) {
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
