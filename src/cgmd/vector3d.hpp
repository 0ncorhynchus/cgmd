#ifndef __MY_VECTOR3D_HPP
#define __MY_VECTOR3D_HPP

#include <vector>

namespace cgmd {

struct Vector3d {
    double x;
    double y;
    double z;
    Vector3d(const double& X, const double& Y, const double& Z)
        : x(X), y(Y), z(Z) {}
    Vector3d() : x(0), y(0), z(0) {}
    Vector3d(const Vector3d &vec)
        : x(vec.x), y(vec.y), z(vec.z) {}
};

using vector_list = std::vector<Vector3d>;

bool operator==(const Vector3d& lhs, const Vector3d& rhs);

Vector3d operator+(const Vector3d& lhs, const Vector3d& rhs);
Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs);
Vector3d operator*(const Vector3d& lhs, const double& rhs);
Vector3d operator/(const Vector3d& lhs, const double& rhs);

Vector3d operator+=(Vector3d& lhs, const Vector3d& rhs);
Vector3d operator-=(Vector3d& lhs, const Vector3d& rhs);

double dot(const Vector3d& lhs, const Vector3d& rhs);
Vector3d cross(const Vector3d& lhs, const Vector3d& rhs);
double norm_sq(const Vector3d& vec);
double norm(const Vector3d& vec);

vector_list operator+(const vector_list& lhs, const vector_list& rhs);
vector_list operator-(const vector_list& lhs, const vector_list& rhs);

vector_list operator+=(vector_list& lhs, const vector_list& rhs);
vector_list operator-=(vector_list& lhs, const vector_list& rhs);

} // cgmd

#endif /* __MY_VECTOR3D_HPP */
