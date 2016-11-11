#ifndef SOLID_H
#define SOLID_H

#include <deque>
#include <iostream>
#include <vector>

#include "point.h"
#include "face.h"

using namespace std;

class Solid {
private:
        int nbVertices, nbFaces, nbEdges;
        deque<Point> points;
        deque<Face> faces;

public:
        Solid();
        Solid(string filepath);
        ~Solid();

        vector<string>	splitLine(string s);
        string			trimLine(string& s);
        double			computeSurface();
};

#endif
