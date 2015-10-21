#include "vector3d.hpp"
#include <cmath>

bool operator==(const Vector3d& lhs, const Vector3d& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

Vector3d operator+(const Vector3d& lhs, const Vector3d& rhs) {
    return Vector3d(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}

Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs) {
    return Vector3d(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}

Vector3d operator*(const Vector3d& lhs, const double& k) {
    return Vector3d(lhs.x*k, lhs.y*k, lhs.z*k);
}

Vector3d operator/(const Vector3d& lhs, const double& k) {
    return Vector3d(lhs.x/k, lhs.y/k, lhs.z/k);
}

double dot(const Vector3d& lhs, const Vector3d& rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

Vector3d cross(const Vector3d& lhs, const Vector3d& rhs) {
    return Vector3d(
            lhs.y*rhs.z-lhs.z*rhs.y,
            lhs.z*rhs.x-lhs.x*rhs.z,
            lhs.x*rhs.y-lhs.y*rhs.x);
}

double norm_sq(const Vector3d& vec) {
    return pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2);
}

double norm(const Vector3d& vec) {
    return sqrt(norm_sq(vec));
}
