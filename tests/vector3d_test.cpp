#include <gtest/gtest.h>
#include <cmath>
#include "vector3d.hpp"

using namespace cgmd;

namespace {

TEST(Vector3dTest, Plus) {
    Vector3d x(1,2,3), y(4,5,5);
    EXPECT_EQ(Vector3d(5,7,8), x + y);
    EXPECT_EQ(Vector3d(5,7,8), y + x);
    x += y;
    EXPECT_EQ(Vector3d(5,7,8), x);
}

TEST(Vector3dTest, Minus) {
    Vector3d x(4,5,5), y(1,2,3);
    EXPECT_EQ(Vector3d(3,3,2), x - y);
    EXPECT_EQ(Vector3d(-3,-3,-2), y - x);
    x -= y;
    EXPECT_EQ(Vector3d(3,3,2), x);
}

TEST(Vector3dTest, Multiple) {
    Vector3d x(4,2,-1);
    EXPECT_EQ(Vector3d(12,6,-3), x * 3);
}

TEST(Vector3dTest, Devision) {
    Vector3d x(4,2,-1);
    EXPECT_EQ(Vector3d(2,1,-0.5), x / 2);
}

TEST(Vector3dTest, Dot) {
    Vector3d x(3,-2,5), y(4,6,0);
    EXPECT_EQ(0, dot(x, y));
    EXPECT_EQ(0, dot(y, x));
}

TEST(Vector3dTest, Cross) {
    Vector3d x(3,-2,5), y(4,6,0);
    EXPECT_EQ(Vector3d(-30,20,26), cross(x, y));
    EXPECT_EQ(Vector3d(30,-20,-26), cross(y, x));
}

TEST(Vector3dTest, NormSquare) {
    Vector3d x(0,1,0), y(1,-2,3);
    EXPECT_EQ(1, norm_sq(x));
    EXPECT_EQ(14, norm_sq(y));
}

TEST(Vector3dTest, Norm) {
    Vector3d x(0,1,0), y(1,-2,3);
    EXPECT_EQ(1, norm(x));
    EXPECT_EQ(sqrt(14), norm(y));
}

TEST(Vector3dListTest, Plus) {
    vector_list x, y, expected;
    x.push_back(Vector3d(0,1,0));
    x.push_back(Vector3d(0,0,1));
    y.push_back(Vector3d(1,2,0));
    y.push_back(Vector3d(0,2,0));
    expected.push_back(Vector3d(1,3,0));
    expected.push_back(Vector3d(0,2,1));
    EXPECT_EQ(expected, x + y);
    x += y;
    EXPECT_EQ(expected, x);
}

TEST(Vector3dListTest, Minus) {
    vector_list x, y, expected;
    x.push_back(Vector3d(0,1,0));
    x.push_back(Vector3d(0,0,1));
    y.push_back(Vector3d(1,2,0));
    y.push_back(Vector3d(0,2,0));
    expected.push_back(Vector3d(-1,-1,0));
    expected.push_back(Vector3d(0,-2,1));
    EXPECT_EQ(expected, x - y);
    x -= y;
    //EXPECT_EQ(expected, x);
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
