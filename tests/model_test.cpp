#include <gtest/gtest.h>
#include <memory>
#include <cgmd/model.hpp>
#include <cgmd/space.hpp>
#include <cgmd/potential/harmonic_bond_potential.hpp>
#include <cgmd/potential/weeks_chandler_anderson_potential.hpp>

using namespace cgmd;

namespace {

class ModelTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        model.reset(2);
        model.set_property(0,/* mass= */1.0,/* friction= */0.4);
        model.set_property(1,/* mass= */1.5,/* friction= */0.3);
        space.reset(2);
        space.coordinate(0) = Vector3d(0,0,1);
        space.coordinate(1) = Vector3d(0,0,2);
    }

    // virtual void TearDown() {}

    Model model;
    Space space;
};

TEST_F(ModelTest, Mass) {
    EXPECT_EQ(1.0, model.get_mass(0));
    EXPECT_EQ(1.5, model.get_mass(1));
}

TEST_F(ModelTest, Friction) {
    EXPECT_EQ(0.4, model.get_friction(0));
    EXPECT_EQ(0.3, model.get_friction(1));
}

TEST_F(ModelTest, BondPotential) {
    ASSERT_EQ(0, model.calculate_energy(space));

    std::shared_ptr<HarmonicBondPotential> bond_potential(new HarmonicBondPotential());
    bond_potential->add_bond(0, 1,/* r= */ 0.5, /* k= */ 2.0);
    model.add_potential(bond_potential);
    EXPECT_EQ(1, model.list_bonds().size());

    EXPECT_NE(0, model.calculate_energy(space));
}

TEST_F(ModelTest, InterPotential) {
    auto potential = std::make_shared<WeeksChandlerAndersonPotential>(
            /* sigma= */1.0, /* epsilon= */1.0);
    EXPECT_EQ(0, model.calculate_energy(space));
    model.add_potential(potential);
    EXPECT_NE(0, model.calculate_energy(space));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
