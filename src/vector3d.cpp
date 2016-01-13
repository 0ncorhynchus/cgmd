#include "vector3d.hpp"
#include <cmath>

namespace cgmd {

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

Vector3d operator+=(Vector3d& lhs, const Vector3d& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

Vector3d operator-=(Vector3d& lhs, const Vector3d& rhs) {
    lhs = lhs - rhs;
    return lhs;
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

vector_list operator+(const vector_list& lhs, const vector_list& rhs) {
    if (lhs.size() != rhs.size())
        return vector_list();
    std::size_t size(lhs.size());
    vector_list sum(size, Vector3d(0,0,0));
    for (std::size_t i(0); i < size; ++i)
        sum[i] = lhs[i] + rhs[i];
    return sum;
}

vector_list operator-(const vector_list& lhs, const vector_list& rhs) {
    if (lhs.size() != rhs.size())
        return vector_list();
    std::size_t size(lhs.size());
    vector_list difference(size, Vector3d(0,0,0));
    for (std::size_t i(0); i < size; ++i)
        difference[i] = lhs[i] - rhs[i];
    return difference;
}

vector_list operator+=(vector_list& lhs, const vector_list& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

vector_list operator-=(vector_list& lhs, const vector_list& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

} // cgmd
