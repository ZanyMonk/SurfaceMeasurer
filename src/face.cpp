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

double Face::computeArea() {
    double area = 0;

    double distances[nbVertices];

    Point* last = back();
    unsigned i = 0;
    for(auto it = begin(); it != end(); it++) {
        distances[i] = (*it)->distanceFrom(last);
        area += distances[i];
        last = (*it);
        i++;
    }

    area /= 2.f;
    double p = area;

    for(unsigned i = 0; i < nbVertices; i++) {
        area *= p-distances[i];
    }

    return sqrt(area);
}
