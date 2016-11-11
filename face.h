#ifndef FACE_H
#define FACE_H

#include <vector>

#include "point.h"

class Face {
private:
        size_t 			nbVertices = 0;
        vector<Point>	vertices;

public:
        Face();
        ~Face();

        void	clear();
        void	setVerticesNumber(size_t n);
        void	addVertex(Point p);
        double	computeSurface();
};

#endif
