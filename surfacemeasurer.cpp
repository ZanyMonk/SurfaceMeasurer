#include "surfacemeasurer.h"

extern bool verbose, timed, omp, analysis;
extern unsigned nbThreads;
const int SurfaceMeasurer::defaultNbThreads = 10;

SurfaceMeasurer::SurfaceMeasurer(std::string filePath)
    :solid(new Solid())
{
    if(analysis) {
        solid->loadFile(filePath);
        runAnalysis();
    } else {
        std::chrono::time_point<std::chrono::system_clock> start, startProcess, end;
        start = std::chrono::system_clock::now();

        // Load solid data
        solid->loadFile(filePath);
        double r;

        startProcess = std::chrono::system_clock::now();

        r = processSolid();

        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed = startProcess-start;
        std::chrono::duration<double> elapsedProcess = end-startProcess;

        std::cout.setf(std::ios::fixed);
        if(verbose) {
            std::cout << "This solid surface is " << r << std::endl;
        } else {
            std::cout << r << std::endl;
        }
        timed && std::cout  << "Processing time :  " << elapsedProcess.count()*1000 << "ms" << std::endl
                            << "Loading time :     " << (elapsed.count()-elapsedProcess.count())*1000 << "ms" << std::endl
                            << "Total time :       " << elapsed.count() << "s" << std::endl
                            << std::setprecision(std::numeric_limits<long double>::digits10 + 1);
    }

}

SurfaceMeasurer::~SurfaceMeasurer() {
    if(solid)
        delete solid;
}

double SurfaceMeasurer::processSolid()
{
    if(!solid || solid->getNbFaces() == 0)
        return 0.f;

    double r;

    // Process data
    if(omp) {
        verbose && std::cout << "Using OpenMP" << std::endl;
        r = solid->computeSurfaceWithOpenMP();
    } else if(nbThreads == 0) {
        verbose && std::cout << "Calculating with sequential algorithm." << std::endl;
        r = solid->computeSurface();
    } else {
        verbose && std::cout << "Calculating with " << nbThreads << " threads." << std::endl;
        r = solid->computeSurfaceWithThreads(nbThreads);
    }

    return r;
}

void SurfaceMeasurer::runAnalysis()
{
    std::chrono::time_point<std::chrono::system_clock> start, startProcess, end;
    start = std::chrono::system_clock::now();

    verbose && std::cout << "Analysis ..." << std::endl;
    std::chrono::duration<double> elapsed = std::chrono::system_clock::now()-start;

    unsigned x = 0;
    double results[5];
    bool tmpVerbose = verbose;
    verbose = false;
    omp = false;
    nbThreads = 0;
    for(unsigned i = 0; i <= 16; i = (i == 0 ? 2 : i*2)) {
        if(i == 16) { // OpenMP
            omp = true;
        } else { // Threads (and no thread)
            omp = false;
            nbThreads = i;
        }

        for(unsigned j = 0; j < 10; j++) {
            startProcess = std::chrono::system_clock::now();

            double r = processSolid();

            end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsedProcess = end-startProcess;

            if(results[x] == 0.f)
                results[x] = elapsedProcess.count()*1000;
            else
                results[x] = (results[x]+elapsedProcess.count()*1000)/2.f;
        }
        x++;
    }
    verbose = tmpVerbose;

    std::cout << "Sequential\t\t" << results[0] << std::endl;
    std::cout << "2 Threads\t\t" << results[1] << std::endl;
    std::cout << "4 Threads\t\t" << results[2] << std::endl;
    std::cout << "8 Threads\t\t" << results[3] << std::endl;
    std::cout << "OpenMP\t\t\t" << results[4] << std::endl;
}

void SurfaceMeasurer::usage() {
    std::cout << "SurfaceMeasurer" << std::endl;
    std::cout << "Usage :\tSurfaceMeasurer [[--threads N|--threads 0|--openmp] [--no-time]|--analysis] <file>" << std::endl;
    std::cout << "<file>             Path to an OFF file" << std::endl;
    std::cout << "-t, --threads N    Use N threads" << std::endl;
    std::cout << "-T, --no-time      No time measure" << std::endl;
    std::cout << "-a, --analysis     Run analysis" << std::endl;
}
