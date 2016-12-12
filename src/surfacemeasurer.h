#ifndef SURFACEMEASURER_H
#define SURFACEMEASURER_H

#include <iomanip>
#include <chrono>
#include <ctime>

#include "solid.h"

class SurfaceMeasurer
{
private:
    Solid *solid;

public:
    static const int    defaultNbThreads;

    SurfaceMeasurer();
    SurfaceMeasurer(std::string filePath);
    ~SurfaceMeasurer();
    double processSolid();
    void runAnalysis();

    static void usage();
};

#endif // SURFACEMEASURER_H
