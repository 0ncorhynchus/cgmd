#include <gtest/gtest.h>
#include "pair_list.hpp"

namespace {

class PairListTest : public ::testing::Test {
protected:
    PairListTest() : pair_list(5) {}

    // virtual void SetUp() {}
    // virtual void TearDown() {}

    PairList pair_list;
};

TEST_F(PairListTest, Iterator) {
    for (int i(0); i < 4; ++i)
        EXPECT_EQ(pair_list.begin(i), pair_list.end(i));
}

TEST_F(PairListTest, AddPair) {
    pair_list.add_pair(std::make_pair(2,3));
    EXPECT_EQ(3, *(pair_list.begin(2)));
    EXPECT_EQ(3, *(pair_list.begin(1)));
    EXPECT_EQ(3, *(pair_list.begin(0)));
    EXPECT_NE(pair_list.begin(2), pair_list.end(2));
    EXPECT_EQ(pair_list.end(2), pair_list.begin(3));
    pair_list.add_pair(std::make_pair(2,4));
    EXPECT_EQ(3, *(pair_list.begin(2)));
    EXPECT_EQ(3, *(pair_list.begin(1)));
    EXPECT_EQ(3, *(pair_list.begin(0)));
    EXPECT_EQ(4, *(++pair_list.begin(2)));
    EXPECT_NE(pair_list.begin(2), pair_list.end(2));
    EXPECT_EQ(pair_list.end(2), pair_list.begin(3));
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
