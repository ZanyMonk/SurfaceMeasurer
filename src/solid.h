#ifndef SOLID_H
#define SOLID_H

#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <omp.h>

#include "point.h"
#include "face.h"

class Solid {
private:
    unsigned            nbVertices,
                        nbFaces,
                        nbEdges,
                        nbThreads;
    std::deque<Point>   points;
    std::deque<Face>    faces;

    std::vector<std::string>    splitLine(std::string s);
    std::string                 trimLine(std::string& s);

public:
    static pthread_mutex_t      resultMutex;

    static const bool           isVertex(std::string &s);

	Solid();
    Solid(std::string filePath);
	~Solid();
    bool loadFile(std::string filePath);

    double                      computeSurface();
    double                      computeSurfaceWithThreads(unsigned nbThreads);
	double						computeSurfaceWithOpenMP();

    inline unsigned getNbFaces() { return nbFaces; }
};

#endif
