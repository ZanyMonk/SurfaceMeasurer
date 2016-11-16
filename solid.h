#ifndef SOLID_H
#define SOLID_H

#include <deque>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "point.h"
#include "face.h"

class Solid {
private:
    int                 nbVertices,
                        nbFaces,
                        nbEdges,
                        nbThreads;
    double              result;
    std::deque<Point>   points;
    std::deque<Face>    faces;

    std::vector<std::string>    splitLine(std::string s);
    std::string                 trimLine(std::string& s);
    void                        computeFaces(int start, int end);

public:
    static const bool   isVertex(std::string &s);
    mutable std::mutex          resultMutex;

	Solid();
    Solid(std::string filepath, int _nbThreads = 10);
    Solid(const Solid& src);
	~Solid();

    double                      computeSurface();
    double                      computeSurfaceWithThreads();
	double						computeSurfaceWithOpenMP();
};

#endif
