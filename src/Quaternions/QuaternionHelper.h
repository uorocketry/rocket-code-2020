#include <cmath>
#include <stdexcept>
#include <iostream>

class Quaternion{
    public:
        Quaternion(double a, double bi, double cj, double dk) {};
        Quaternion conj(){};
        std::string output(){};
        Quaternion toPoint(){};
        Quaternion add(Quaternion q){};
        Quaternion sub(Quaternion q){};
        Quaternion mul(Quaternion q){};

};

class Point3D: Quaternion{
    public:
        Point3D() : Quaternion(0, 0, 0, 0){};
        Point3D(double bi, double cj, double dk) : Quaternion(0, bi, cj, dk){};
        Point3D add(Point3D p, Point3D p2){};
        Point3D sub(Point3D p, Point3D p2){};
        std::string output(){};
        Point3D transform(Quaternion q){};
};