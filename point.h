#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class Point {
public:
    double x, y, z;

    Point();
    Point(double _x, double _y, double _z);
    ~Point();

    void setPosition(double _x, double _y, double _z);
    void setPosition(std::string _x, std::string _y, std::string _z);
    double distanceFrom(Point* p);

    friend std::ostream&  operator<<(std::ostream&, const Point&);
};

#endif
