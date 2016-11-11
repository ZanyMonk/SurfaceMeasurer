#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point {
public:
        double x, y, z;

        Point();
        Point(double _x, double _y, double _z);
        ~Point();

        void setPosition(double _x, double _y, double _z);
        void setPosition(string _x, string _y, string _z);
        double distanceFrom(Point* p);

        friend std::ostream&  operator<<(std::ostream&, const Point&);
};

#endif
