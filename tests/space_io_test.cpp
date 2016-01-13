#include <gtest/gtest.h>
#include <cgmd/space_io.hpp>
#include <cgmd/space_xyz_io.hpp>

using namespace cgmd;

namespace {

class SpaceXYZIOTest : public ::testing::Test {
protected:
    SpaceXYZIOTest() :
        writer("/tmp/space_xyz_test.xyz"),
        reader("/tmp/space_xyz_test.xyz") {}

    SpaceXYZWriter writer;
    SpaceXYZReader reader;
};

TEST_F(SpaceXYZIOTest, Validation) {
    Space origin(2);
    origin.symbol(0) = "A";
    origin.coordinate(0) = Vector3d(0,0,0);
    origin.symbol(1) = "B";
    origin.coordinate(1) = Vector3d(1,0,0);
    writer.save(origin);
    Space space;
    reader.load(space);
    EXPECT_EQ(2, space.num_beads());
    EXPECT_EQ("A", space.symbol(0));
    EXPECT_EQ("B", space.symbol(1));
    EXPECT_EQ(Vector3d(0,0,0), space.coordinate(0));
    EXPECT_EQ(Vector3d(1,0,0), space.coordinate(1));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
