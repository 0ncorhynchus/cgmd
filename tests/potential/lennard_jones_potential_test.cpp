#include <gtest/gtest.h>
#include <cmath>
#include <cgmd/space.hpp>
#include <cgmd/potential/lennard_jones_potential.hpp>

using namespace cgmd;

namespace {

class LennardJonesPotentialTest : public ::testing::Test {
protected:
    LennardJonesPotentialTest() : potential(/* sigma= */1.0, /* epsilon= */0.25) {}

    // virtual void SetUp() {}

    // virtual void TearDown() {}

    LennardJonesPotential potential;
};

TEST_F(LennardJonesPotentialTest, CalculateEnergy) {
    Space space(2);
    space.coordinate(0) = Vector3d(0,0,0);
    space.coordinate(1) = Vector3d(2,0,0);

    EXPECT_EQ(pow(0.5,12) - pow(0.5,6), potential.calculate_energy(space));
}

TEST_F(LennardJonesPotentialTest, CalculateForce) {
    Space space(2);
    space.coordinate(0) = Vector3d(0,0,0);
    space.coordinate(1) = Vector3d(2,0,0);

    const double strength(-3*(2*pow(0.5,12)-pow(0.5,6)));
    vector_list expected(2);
    expected.at(0) = Vector3d(1,0,0) * strength;
    expected.at(1) = expected.at(0) * (-1);
    EXPECT_EQ(expected, potential.calculate_force(space));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
