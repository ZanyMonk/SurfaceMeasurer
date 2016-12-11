#ifndef FACE_H
#define FACE_H

#include <vector>

#include "point.h"

class Face {
private:
    size_t 			nbVertices = 0;
    std::vector<Point*>	vertices;

public:
    Face();
    ~Face();

    void	clear();
    void	setVerticesNumber(size_t n);
    void	addVertex(Point* p);
    static double	computeArea(Face *face);

    inline size_t size() { return nbVertices; }
    inline Point* back() { return vertices.back(); }
    inline std::vector<Point*>::const_iterator begin() { return vertices.cbegin(); }
    inline std::vector<Point*>::const_iterator end() { return vertices.cend(); }
};

#endif
