#ifndef SOLID_H
#define SOLID_H

#include <deque>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <pthread.h>
//#include <thread>
//#include <mutex>

#include "point.h"
#include "face.h"

class Solid {
private:
    int                 nbVertices,
                        nbFaces,
                        nbEdges,
                        nbThreads;
    std::deque<Point>   points;
    std::deque<Face>    faces;

    std::vector<std::string>    splitLine(std::string s);
    std::string                 trimLine(std::string& s);

public:
    static const bool           isVertex(std::string &s);
    static pthread_mutex_t      resultMutex;

	Solid();
    Solid(std::string filepath);
	~Solid();

    double                      computeSurface();
    double                      computeSurfaceWithThreads(int nbThreads);
	double						computeSurfaceWithOpenMP();
};

#endif
