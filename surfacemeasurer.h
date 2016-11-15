#ifndef SURFACEMEASURER_H
#define SURFACEMEASURER_H

#include "solid.h"

class SurfaceMeasurer
{
private:
    Solid* solid;

public:
    static const int    defaultNbThreads;

    SurfaceMeasurer();
    SurfaceMeasurer(std::string filePath, int nbThreads);
    ~SurfaceMeasurer();

    static void usage();
};

#endif // SURFACEMEASURER_H
