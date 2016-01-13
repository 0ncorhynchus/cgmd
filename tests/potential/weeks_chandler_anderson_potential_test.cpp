#include <gtest/gtest.h>
#include <cmath>
#include <cgmd/space.hpp>
#include <cgmd/pair_list.hpp>
#include <cgmd/potential/weeks_chandler_anderson_potential.hpp>
#include <limits>

using namespace cgmd;

namespace {

class WeeksChandlerAndersonPotentialTest : public ::testing::Test {
protected:
    WeeksChandlerAndersonPotentialTest() :
            potential(/* sigma= */1.0, /* epsilon= */0.25),
            space(2) {
        space.coordinate(0) = Vector3d(0.0, 0.0, 0.0);
        space.coordinate(1) = Vector3d(0.9, 0.0, 0.0);
        space.symbol(0) = "A";
        space.symbol(1) = "B";
    }

    // virtual void SetUp() {}

    // virtual void TearDown() {}

    WeeksChandlerAndersonPotential potential;
    Space space;
};

TEST_F(WeeksChandlerAndersonPotentialTest, CutoffRadius) {
    EXPECT_EQ(pow(2.0,1.0/6.0), potential.get_cutoff_radius());
}

TEST_F(WeeksChandlerAndersonPotentialTest, Pair) {
    EXPECT_TRUE(potential.is_valid_pair("A", "B"));
    EXPECT_TRUE(potential.is_valid_pair("B", "A"));
    EXPECT_NE(0, potential.calculate_energy(space));

    potential.set_pair("A", "B");
    EXPECT_TRUE(potential.is_valid_pair("A", "B"));
    EXPECT_TRUE(potential.is_valid_pair("B", "A"));
    EXPECT_NE(0, potential.calculate_energy(space));

    potential.set_pair("A", "C");
    EXPECT_FALSE(potential.is_valid_pair("A", "B"));
    EXPECT_FALSE(potential.is_valid_pair("B", "A"));
    EXPECT_EQ(0, potential.calculate_energy(space));
}

TEST_F(WeeksChandlerAndersonPotentialTest, NeighborList) {
    auto neighbor_list = std::make_shared<PairList>(2);
    potential.set_neighbor_list(neighbor_list);
    EXPECT_EQ(0, potential.calculate_energy(space));
    neighbor_list->add_pair(std::make_pair(0, 1));
    EXPECT_NE(0, potential.calculate_energy(space));
}

TEST_F(WeeksChandlerAndersonPotentialTest, CalculateEnergy) {
    const double R6(pow(1.0/0.9,6));
    EXPECT_EQ(pow(R6, 2.0)-R6+0.25, potential.calculate_energy(space));
}

TEST_F(WeeksChandlerAndersonPotentialTest, Validation) {
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
