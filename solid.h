#ifndef SOLID_H
#define SOLID_H

#include <deque>
#include <iostream>
#include <vector>
#include <thread>

#include "point.h"
#include "face.h"

using namespace std;


class Solid {
private:
        int nbVertices, nbFaces, nbEdges, nbThreads;
        deque<Point>    points;
        deque<Face>     faces;
        vector<thread>  threads();

public:
        Solid();
        Solid(string filepath);
        ~Solid();

        vector<string>	splitLine(string s);
        string			trimLine(string& s);
        double			computeSurface();
        static const int defaultNbThreads;
};

#endif
