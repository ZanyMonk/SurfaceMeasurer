#include <fstream>
#include <sstream>

#include "Solid.h"

Solid::Solid() {
        nbVertices = 0;
        nbFaces = 0;
        nbEdges = 0;
}

Solid::Solid(string filepath) {
        string line;
        ifstream file;
        file.open(filepath);

        if(file.is_open()) {
                getline(file, line); // Check first line
                if(line != "OFF") {
                        cerr << "Bad file format." << endl;
                } else {
                        // Retrieve number of vertices, faces and edges
                        getline(file, line);
                        vector<string> infos = splitLine(trimLine(line));
                        nbVertices = stoi(infos[0]);
                        nbFaces = stoi(infos[1]);
                        nbEdges = stoi(infos[2]);

                        // cout << "Nombre de sommets : " << nbVertices << endl;
                        // cout << "Nombre de faces : " << nbFaces << endl;
                        // cout << "Nombre d'arêtes : " << nbEdges << endl;

                        Point   pointBuffer;
                        Face    faceBuffer;
                        // Read points and faces definition
                        while(getline(file, line)) {
                                vector<string> v = splitLine(trimLine(line));

                                // Check if line is a comment
                                if(line[0] == '#') {
                                        continue;
                                }

                                // If not, treat the line as
                                if(isVertex(line)) {    // vertex coords
                                        pointBuffer.setPosition(v[0], v[1], v[2]);
                                        points.push_back(pointBuffer);
                                } else {        // face coords
                                        size_t n = stoi(v[0]);
                                        faceBuffer.clear();
                                        faceBuffer.setVerticesNumber(n);
                                        for (size_t i = n; i > 0; i--) {
                                                faceBuffer.addVertex(points[stoi(v[i-1])]);
                                        }
                                        faces.push_back(faceBuffer);
                                }
                        }
                }
        } else {
                cerr << "Couldn't open file at \"" << filepath << "\"." << endl;
        }

        file.close();
}

Solid::~Solid() { }

vector<string> Solid::splitLine(string s) {
        stringstream stream;
        stream.str(s);
        vector<string> ret;
        string buffer;

        while(getline(stream, buffer, ' ')) {
                if(!buffer.empty()) {
                        ret.push_back(buffer);
                }
        }

        return ret;
}

string Solid::trimLine(string& s) {
        size_t f = s.find_first_not_of(' ');
        size_t l = s.find_last_not_of(' ');
        s = s.substr(f, l-f+1);

        return s;
}

double Solid::computeSurface() {
        double surface = 0.f;

        for(Face f : faces) {
                surface += f.computeSurface();
        }

        return surface;
}


bool Solid::isVertex(string &s){
        if(s[0] == '-' || s[0] == '0' ) return true;
        size_t i = 0;
        while(s[i] != ' '){
                if(s[i] == '.'){
                        return true;
                }
        }
        return false;
}
