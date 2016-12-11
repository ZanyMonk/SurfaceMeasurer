#include "face.h"

using namespace std;

Face::Face() { }
Face::~Face() { }

void Face::clear() {
    nbVertices = 0;
    vertices.clear();
}

void Face::setVerticesNumber(size_t n) {
    nbVertices = n;
}

void Face::addVertex(Point *p) {
    if(vertices.size() < nbVertices) {
        vertices.push_back(p);
    } else {
        cerr << "Bad number of vertices. Cannot add vertex." << endl;
    }
}

double Face::computeArea(Face *face) {
    double area = 0;

    double distances[face->nbVertices];

    Point* last = face->back();
    unsigned i = 0;
    for(auto it = face->begin(); it != face->end(); it++) {
        distances[i] = (*it)->distanceFrom(last);
        area += distances[i];
        last = (*it);
        i++;
    }

    std::cout << " 0: " << distances[0]<< " 1: " << distances[1]<< " 2: " << distances[2] << std::endl;

    area /= 2.f;
    double p = area;

    for(unsigned i = 0; i < face->nbVertices; i++) {
        area *= p-distances[i];
    }

    return sqrt(area);
}
