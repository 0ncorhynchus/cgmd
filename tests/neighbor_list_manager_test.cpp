#include <gtest/gtest.h>
#include "neighbor_list_manager.hpp"

namespace {

class NeighborListManagerTest : public ::testing::Test {
protected:
    NeighborListManagerTest() : manager(10, 0.5, 1.5) {}

    // virtual void SetUp() {}
    // virtual void TearDown() {}

    NeighborListManager manager;
};

TEST_F(NeighborListManagerTest, Constructor) {}

TEST_F(NeighborListManagerTest, UpdateFlag) {
    EXPECT_EQ(false, manager.to_update());
    std::list<double> displacements(10, 0.0);
    auto itr(displacements.begin());
    *itr = 0.4;
    ++itr;
    *itr = 0.61;
    manager.add_displacements(displacements);
    EXPECT_EQ(true, manager.to_update());
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
