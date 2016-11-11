#ifndef SOLID_H
#define SOLID_H

#include <deque>
#include <iostream>
#include <vector>

#include "Point.h"
#include "Face.h"

using namespace std;

class Solid {
private:
	int nbVertices, nbFaces, nbEdges;
	deque<Point> points;
	deque<Face> faces;

public:
	Solid();
	Solid(string filepath);
	~Solid();
	static bool isVertex(string &s);

	vector<string>	splitLine(string s);
	string			trimLine(string& s);
	double			computeSurface();
};

#endif
