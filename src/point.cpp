#include "point.h"

Point::Point() {
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

Point::~Point() { }

void Point::setPosition(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

void Point::setPosition(std::string _x, std::string _y, std::string _z) {
    x = stod(_x);
    y = stod(_y);
    z = stod(_z);
}

double Point::distanceFrom(Point* p) {
    return sqrt(pow(p->x-x, 2)+pow(p->y-y, 2)+pow(p->z-z, 2));
}

// Debug purposes
std::ostream& operator<<(std::ostream& _os, const Point & _p) {
    _os << "(" << _p.x <<"," << _p.y << "," << _p.z  << ")";

    return(_os);
}
