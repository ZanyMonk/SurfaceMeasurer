#include "surfacemeasurer.h"

extern bool verbose, timed, omp;
const int SurfaceMeasurer::defaultNbThreads = 10;

SurfaceMeasurer::SurfaceMeasurer(
    std::string filePath,
    unsigned nbThreads
)
    :solid(filePath)
{
    std::chrono::time_point<std::chrono::system_clock> start, startProcess, end;

    start = std::chrono::system_clock::now();

    // Load solid data
    double r;

    startProcess = std::chrono::system_clock::now();

    // Process data
    if(omp) {
        verbose && std::cout << "Using OpenMP" << std::endl;
        r = solid.computeSurfaceWithOpenMP();
    } else if(nbThreads == 0) {
        r = solid.computeSurface();
    } else {
        verbose && std::cout << "Calculating with " << nbThreads << " threads." << std::endl;
        r = solid.computeSurfaceWithThreads(nbThreads);
    }

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = end-start;
    std::chrono::duration<double> elapsedProcess = end-startProcess;

    std::cout.setf(std::ios::fixed);
    if(verbose) {
        std::cout << "This solid surface is " << r << std::endl;
    } else {
        std::cout << r << std::endl;
    }
    timed && std::cout  << "Processing time :  " << elapsedProcess.count() << "s" << std::endl
                        << "Loading time :     " << elapsed.count()-elapsedProcess.count() << "s" << std::endl
                        << "Total time :       " << elapsed.count() << "s" << std::endl
                        << std::setprecision(std::numeric_limits<long double>::digits10 + 1);
}

SurfaceMeasurer::~SurfaceMeasurer() { }

void SurfaceMeasurer::usage() {
    std::cout << "SurfaceMeasurer" << std::endl;
    std::cout << "Usage :\tSurfaceMeasurer [-t N] <file>" << std::endl;
    std::cout << "<file>\t\tPath to an OFF file" << std::endl;
    std::cout << "-t N\t\tUse N threads" << std::endl;
}
