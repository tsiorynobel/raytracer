#include "vector.h"

Vector::Vector(double x, double y, double z) : _x(x), _y(y), _z(z) {}

double Vector::x() const { return _x; }
double Vector::y() const { return _y; }
double Vector::z() const { return _z; }

Vector Vector::add(const Vector& other) const {
    return Vector(_x + other._x, _y + other._y, _z + other._z);
}
