#include <gtest/gtest.h>
#include "space.hpp"

using namespace cgmd;

namespace {

class SpaceTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        space.reset(15);
        for (int i(0); i < 10; ++i)
            space.coordinate(i) = Vector3d(i,0,0);

        space.coordinate(10) = Vector3d(2,2,2);
        space.coordinate(11) = Vector3d(2,1,2);
        space.coordinate(12) = Vector3d(2,3,2);
        space.coordinate(13) = Vector3d(2,2,1);
        space.coordinate(14) = Vector3d(2,2,3);

        for (int i(0); i < 15; ++i) {
            space.symbol(i) = "A";
        }
    }

    // virtual void TearDown() {}

    Space space;
};

TEST_F(SpaceTest, NumBeads) {
    EXPECT_EQ(15, space.num_beads());
}

TEST_F(SpaceTest, Time) {
    EXPECT_EQ(0, space.t());
    space.set_t(0.2);
    EXPECT_EQ(0.2, space.t());
}

TEST_F(SpaceTest, Symbols) {
    EXPECT_EQ("A", space.symbol(1));
    space.symbol(1) = "B";
    EXPECT_EQ("B", space.symbol(1));
}

TEST_F(SpaceTest, Coordinates) {
    EXPECT_EQ(Vector3d(4,0,0), space.coordinate(4));
    EXPECT_EQ(Vector3d(2,2,3), space.coordinate(14));
}

TEST_F(SpaceTest, Veclotities) {
    EXPECT_EQ(Vector3d(0,0,0), space.velocity(11));
    space.velocity(11) = Vector3d(1,1,1);
    EXPECT_EQ(Vector3d(1,1,1), space.velocity(11));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
