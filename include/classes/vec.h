//
// Created by Murilo on 25/04/2024.
//

#ifndef CG2_VEC_H
#define CG2_VEC_H

#include <cmath>

class Vec {
public:
    double x, y, z, w;

    // Construtores
    Vec() : x(0), y(0), z(0), w(1) {}
    Vec(double _x, double _y, double _z) : x(_x), y(_y), z(_z), w(1) {}
    Vec(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}

    // Operadores
    Vec operator+(const Vec& v) const {return Vec(v.x + x, v.y + y, v.z + z);}

    Vec operator-(const Vec& v) const {return Vec(x - v.x, y - v.y, z - v.z, w - v.w);}

    Vec operator*(const double d) const {return Vec(x * d, y * d, z * d);}

    Vec operator*(const Vec& v) const {return Vec(x * v.x, y * v.y, z * v.z);}

    Vec operator/(const double d) const {return Vec(x / d, y / d, z / d);}

    double dot(const Vec& v) const {return v.x * x + v.y * y + v.z * z;}

    Vec operator&(const Vec& v) const {
        return Vec((y * v.z) - (z * v.y),
                   (z * v.x) - (x * v.z),
                   (x * v.y) - (y * v.x));
    }

    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vec normalize() const {
        double len = magnitude();
        return Vec(x / len, y / len, z / len);
    }
};

#endif //CG2_VEC_H
