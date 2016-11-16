#ifndef SURFACEMEASURER_H
#define SURFACEMEASURER_H

#include <chrono>
#include <ctime>

#include "solid.h"

class SurfaceMeasurer
{
private:
    Solid* solid;

public:
    static const int    defaultNbThreads;

    SurfaceMeasurer();
    SurfaceMeasurer(std::string filePath, unsigned nbThreads);
    ~SurfaceMeasurer();

    static void usage();
};

#endif // SURFACEMEASURER_H
