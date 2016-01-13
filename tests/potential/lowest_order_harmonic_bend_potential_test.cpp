#include <gtest/gtest.h>
#include <cmath>
#include <cgmd/space.hpp>
#include <cgmd/potential/lowest_order_harmonic_bend_potential.hpp>

using namespace cgmd;

namespace {

class LowestOrderHarmonicBendPotentialTest : public ::testing::Test {
protected:
    LowestOrderHarmonicBendPotentialTest() :
            potential(
                /* r0 = */1.5,
                /* k = */2.0),
            space(2) {
        potential.add_pair(std::make_pair(0, 1));
        space.coordinate(0) = Vector3d(0.0, 0.0, 0.0);
        space.coordinate(1) = Vector3d(1.0, 0.0, 0.0);
    }

    // virtual void SetUp() {}
    // virtual void TearDown() {}

    LowestOrderHarmonicBendPotential potential;
    Space space;
};

TEST_F(LowestOrderHarmonicBendPotentialTest, CalculateEnergy) {
    EXPECT_EQ(pow(0.5,2), potential.calculate_energy(space));
}

TEST_F(LowestOrderHarmonicBendPotentialTest, Validation) {
    vector_list perturbation(2);
    perturbation.at(0) = Vector3d(0, 0, 1.0e-4);
    perturbation.at(1) = Vector3d(0, 1.0e-4, 0);

    vector_list forces(potential.calculate_force(space));
    double energy(potential.calculate_energy(space));
    energy += dot(forces.at(0), perturbation.at(0));
    energy += dot(forces.at(1), perturbation.at(1));

    space.coordinate(0) += perturbation.at(0);
    space.coordinate(1) += perturbation.at(1);

    EXPECT_NEAR(energy, potential.calculate_energy(space), 5.0e-7);
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
