#include <gtest/gtest.h>
#include "neighbor_list.hpp"

namespace {

class NeighborListTest : public ::testing::Test {
protected:
    NeighborListTest() : neighbor_list(5) {}

    // virtual void SetUp() {}
    // virtual void TearDown() {}

    NeighborList neighbor_list;
};

TEST_F(NeighborListTest, Iterator) {
    for (int i(0); i < 5; ++i)
        EXPECT_EQ(neighbor_list.begin(i), neighbor_list.end(i));
}

TEST_F(NeighborListTest, AddPair) {
    neighbor_list.add_pair(2,3);
    EXPECT_EQ(3, *(neighbor_list.begin(2)));
    EXPECT_EQ(3, *(neighbor_list.begin(1)));
    EXPECT_EQ(3, *(neighbor_list.begin(0)));
    EXPECT_NE(neighbor_list.begin(2), neighbor_list.end(2));
    EXPECT_EQ(neighbor_list.end(2), neighbor_list.begin(3));
    EXPECT_EQ(neighbor_list.end(2), neighbor_list.begin(4));
    neighbor_list.add_pair(2,4);
    EXPECT_EQ(3, *(neighbor_list.begin(2)));
    EXPECT_EQ(3, *(neighbor_list.begin(1)));
    EXPECT_EQ(3, *(neighbor_list.begin(0)));
    EXPECT_EQ(4, *(++neighbor_list.begin(2)));
    EXPECT_NE(neighbor_list.begin(2), neighbor_list.end(2));
    EXPECT_EQ(neighbor_list.end(2), neighbor_list.begin(3));
    EXPECT_EQ(neighbor_list.end(2), neighbor_list.begin(4));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
