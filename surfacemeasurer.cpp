#include "surfacemeasurer.h"

const int SurfaceMeasurer::defaultNbThreads = 10;

SurfaceMeasurer::SurfaceMeasurer(
        std::string filePath,
        unsigned nbThreads
) {
    solid = new Solid(filePath);
    double r;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    if(nbThreads == 0) {
        r = solid->computeSurface();
    } else {
        std::cout << "Calculating with " << nbThreads << " threads." << std::endl;
        r = solid->computeSurfaceWithThreads(nbThreads);
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end-start;
    std::cout << "This solid surface is " << r << std::endl
              << "Done in " << elapsed.count() << "s" << std::endl;
}

SurfaceMeasurer::~SurfaceMeasurer() {
    if(solid) {
        delete solid;
    }
}

void SurfaceMeasurer::usage() {
    std::cout << "SurfaceMeasurer" << std::endl;
    std::cout << "Usage :\tSurfaceMeasurer [-t N] <file>" << std::endl;
    std::cout << "<file>\t\tPath to an OFF file" << std::endl;
    std::cout << "-t N\t\tUse N threads" << std::endl;
}
