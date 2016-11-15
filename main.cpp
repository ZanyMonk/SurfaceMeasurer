#include <fstream>
#include <cstring>

#include "surfacemeasurer.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 2) {
        SurfaceMeasurer::usage();
        return 1;
    }

    int nbThreads = SurfaceMeasurer::defaultNbThreads;

    for(size_t i = 1; i < argc; i++) {
        std::ifstream f(argv[i]);
        if(f.is_open()) { // File exists ?
            SurfaceMeasurer sm(argv[i], nbThreads);
        } else if(strcmp("-t", argv[i]) == 0) {
            nbThreads = atoi(argv[i+1]);
        }

    }

    return 0;
}
