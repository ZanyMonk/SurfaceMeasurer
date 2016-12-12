#include <unistd.h>

#include <fstream>
#include <cstring>

#include "surfacemeasurer.h"

bool verbose = false, timed = true, omp = false, analysis = false;
unsigned nbThreads = 0;

int main(int argc, char** argv) {
    if(argc < 2) {
        SurfaceMeasurer::usage();
        return 1;
    }

    for(std::uintmax_t i = 1; i < argc; i++) {
        std::ifstream f(argv[i]);
        if(f.is_open()) { // File exists ?
            SurfaceMeasurer sm(argv[i]);
            return 0;
        } else if(strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
            SurfaceMeasurer::usage();
            return 0;
        } else if(strcmp("-omp", argv[i]) == 0 || strcmp("--openmp", argv[i]) == 0) {
            omp = true;
        } else if(strcmp("-t", argv[i]) == 0 || strcmp("--threads", argv[i]) == 0) {
            nbThreads = atoi(argv[i+1]);
            i++;
        } else if(strcmp("-v", argv[i]) == 0 || strcmp("--verbose", argv[i]) == 0) {
            verbose = true;
        } else if(strcmp("-T", argv[i]) == 0 || strcmp("--no-time", argv[i]) == 0) {
            timed = false;
        } else if(strcmp("-a", argv[i]) == 0 || strcmp("--analysis", argv[i]) == 0) {
            verbose = true;
            analysis = true;
        } else {
            std::cerr << "Unkown option '" << argv[i] << "'." << std::endl;
            SurfaceMeasurer::usage();
            return 1;
        }
    }

    return 0;
}
