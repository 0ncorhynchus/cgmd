#include <gtest/gtest.h>
#include <memory>
#include <cgmd/model.hpp>
#include <cgmd/potential/harmonic_bond_potential.hpp>

using namespace cgmd;

namespace {

class ModelTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        model.reset(2);
        model.set_property(0,/* mass= */1.0,/* friction= */0.4);
        model.set_property(1,/* mass= */1.5,/* friction= */0.3);
    }

    // virtual void TearDown() {}

    Model model;
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
    std::shared_ptr<HarmonicBondPotential> bond_potential(new HarmonicBondPotential());
    bond_potential->add_bond(0, 1,/* r= */ 0.5, /* k= */ 2.0);
    model.add_potential(bond_potential);
    EXPECT_EQ(1, model.list_bonds().size());
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
