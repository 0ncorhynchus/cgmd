#include <gtest/gtest.h>
#include <cgmd/periodic_space.hpp>

using namespace cgmd;

namespace {

class PeriodicSpaceTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        space.reset(2);
        space.set_lengths(5, 5, 5);
        space.coordinate(0) = Vector3d(1, 1, 1);
        space.coordinate(1) = Vector3d(4, 4, 4);
        space.symbol(0) = "A";
        space.symbol(1) = "B";
    }

    // virtual void TearDown() {}

    PeriodicSpace space;
};

TEST_F(PeriodicSpaceTest, NumBeads) {
    EXPECT_EQ(2, space.num_beads());
}

TEST_F(PeriodicSpaceTest, Reset) {
    ASSERT_EQ(2, space.num_beads());
    space.reset(10);
    EXPECT_EQ(10, space.num_beads());
}

TEST_F(PeriodicSpaceTest, Time) {
    EXPECT_EQ(0, space.t());
    space.set_t(0.2);
    EXPECT_EQ(0.2, space.t());
}

TEST_F(PeriodicSpaceTest, Symbols) {
    EXPECT_EQ("A", space.symbol(0));
    space.symbol(0) = "C";
    EXPECT_EQ("C", space.symbol(0));
}

TEST_F(PeriodicSpaceTest, Coordinates) {
    EXPECT_EQ(Vector3d(1,1,1), space.coordinate(0));
    EXPECT_EQ(Vector3d(4,4,4), space.coordinate(1));
}

TEST_F(PeriodicSpaceTest, Veclotities) {
    EXPECT_EQ(Vector3d(0,0,0), space.velocity(1));
    space.velocity(1) = Vector3d(1,1,1);
    EXPECT_EQ(Vector3d(1,1,1), space.velocity(1));
}

TEST_F(PeriodicSpaceTest, Move) {
    ASSERT_EQ(Vector3d(1,1,1), space.coordinate(0));
    space.move(0, Vector3d(2,2,2));
    EXPECT_EQ(Vector3d(3,3,3), space.coordinate(0));
    space.move(0, Vector3d(3,3,3));
    EXPECT_EQ(Vector3d(1,1,1), space.coordinate(0));
}

TEST_F(PeriodicSpaceTest, Direct) {
    EXPECT_EQ(Vector3d(-2,-2,-2), space.direct(0,1));
    EXPECT_EQ(Vector3d(2,2,2), space.direct(1,0));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
