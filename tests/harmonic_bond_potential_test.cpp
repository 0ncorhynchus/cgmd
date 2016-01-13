#include <gtest/gtest.h>
#include <cmath>
#include "space.hpp"
#include "harmonic_bond_potential.hpp"

using namespace cgmd;

namespace {

class HarmonicBondPotentialTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        potential.add_bond(0,1,/* r= */0.5,/* k= */2.0);
        potential.add_bond(0,2,/* r= */0.6,/* k= */2.5);
    }

    // virtual void TearDown() {}

    HarmonicBondPotential potential;
};

TEST_F(HarmonicBondPotentialTest, AddBond) {
    EXPECT_TRUE(potential.add_bond(3,2,/* r= */0.6,/* k= */2.5));
    EXPECT_FALSE(potential.add_bond(1,0,/* r= */0.57,/* k= */2.0));
}

TEST_F(HarmonicBondPotentialTest, ListBonds) {
    EXPECT_EQ(2, potential.list_bonds().size());
}

TEST_F(HarmonicBondPotentialTest, R) {
    EXPECT_EQ(0.5, potential.get_r(0,1));
    EXPECT_EQ(0.5, potential.get_r(1,0));
    EXPECT_EQ(0.6, potential.get_r(0,2));
    EXPECT_EQ(0.6, potential.get_r(2,0));
    EXPECT_EQ(0.0, potential.get_r(1,2));
    EXPECT_EQ(0.0, potential.get_r(2,1));
}

TEST_F(HarmonicBondPotentialTest, K) {
    EXPECT_EQ(2.0, potential.get_k(0,1));
    EXPECT_EQ(2.0, potential.get_k(1,0));
    EXPECT_EQ(2.5, potential.get_k(0,2));
    EXPECT_EQ(2.5, potential.get_k(2,0));
    EXPECT_EQ(0.0, potential.get_k(1,2));
    EXPECT_EQ(0.0, potential.get_k(2,2));
}

TEST_F(HarmonicBondPotentialTest, CalculateEnergy) {
    Space space(2);
    space.coordinate(0) = Vector3d(0,0,0);
    space.coordinate(1) = Vector3d(2,0,0);

    EXPECT_EQ(2.0*pow(2-0.5,2), potential.calculate_energy(space));
}

TEST_F(HarmonicBondPotentialTest, CalculateForce) {
    Space space(2);
    space.coordinate(0) = Vector3d(0,0,0);
    space.coordinate(1) = Vector3d(2,0,0);

    const double strength(2.0*2.0*(2-0.5));
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
