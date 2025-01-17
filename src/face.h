#ifndef FACE_H
#define FACE_H

#include <vector>

#include "point.h"

class Face {
private:
    std::uintmax_t 			nbVertices = 0;
    std::vector<Point*>	vertices;

public:
    Face();
    ~Face();

    void	clear();
    void	setVerticesNumber(std::uintmax_t n);
    void	addVertex(Point* p);
    double	computeArea();

    inline std::uintmax_t size() { return nbVertices; }
    inline Point* back() { return vertices.back(); }
    inline std::vector<Point*>::const_iterator begin() { return vertices.cbegin(); }
    inline std::vector<Point*>::const_iterator end() { return vertices.cend(); }
};

#endif
