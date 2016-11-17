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

void Face::addVertex(Point p) {
    if(vertices.size() < nbVertices) {
        vertices.push_back(p);
    } else {
        cerr << "Bad number of vertices. Cannot add vertex." << endl;
    }
}

double Face::computeSurface() {
    double surface = 0;

    Point* last = &vertices.back();
    for(vector<Point>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        surface += it->distanceFrom(last);
        last = &(*it);
    }

    return surface;
}
