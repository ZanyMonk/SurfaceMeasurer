#include "surfacemeasurer.h"

const int SurfaceMeasurer::defaultNbThreads = 10;

SurfaceMeasurer::SurfaceMeasurer(
        std::string filePath,
        int nbThreads = defaultNbThreads
) {
    cout << "With " << nbThreads << " threads." << endl;

    solid = new Solid(filePath);

	cout << "This solid surface is " << solid->computeSurfaceWithThreads() << endl;
	cout << "This solid surface is " << solid->computeSurfaceWithOpenMP() << " open mp"<<endl;

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
