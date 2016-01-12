#include <gtest/gtest.h>
#include "neighbor_list_manager.hpp"

namespace {

class NeighborListManagerTest : public ::testing::Test {
protected:
    NeighborListManagerTest() : manager(10, 0.5, 1.5, 1.0e-3) {}

    // virtual void SetUp() {}
    // virtual void TearDown() {}

    NeighborListManager manager;
};

TEST_F(NeighborListManagerTest, Constructor) {}

TEST_F(NeighborListManagerTest, UpdateFlag) {
    EXPECT_EQ(true, manager.to_update(1.0e-3));
    EXPECT_EQ(false, manager.to_update(0.0));
    std::list<double> displacements(10, 0.0);
    auto itr(displacements.begin());
    *itr = 0.4;
    ++itr;
    *itr = 0.61;
    manager.add_displacements(displacements);
    EXPECT_EQ(true, manager.to_update(0.0));
}

TEST_F(NeighborListManagerTest, Update) {
    Space space(10);
    for (int i(0); i < 10; ++i)
        space.coordinate(i) = Vector3d(0,0,0.5*i);
    manager.add_candidate(std::make_pair(0,1));
    manager.add_candidate(std::make_pair(0,3));
    manager.update(space);
    std::shared_ptr<PairList> neighbor_list(manager.get_neighbor_list());
    auto itr(neighbor_list->begin(0));
    EXPECT_EQ(1, *itr);
    ++itr;
    EXPECT_EQ(3, *itr);
    ++itr;
    EXPECT_EQ(neighbor_list->end(0), itr);
    for (int i(1); i < 9; ++i)
        EXPECT_EQ(neighbor_list->begin(i), neighbor_list->end(i));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
