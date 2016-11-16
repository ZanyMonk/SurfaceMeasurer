#include <fstream>
#include <sstream>

#include "solid.h"

void* computeFaces(void* data)
{
    double* r = new double(0.f);
    std::deque<Face*>* faces = (std::deque<Face*>*)data;
    for(size_t i = 0; i < faces->size(); i++) {
        (*r) += faces->at(i)->computeSurface();
    }

    return r;
}

Solid::Solid(std::string filepath) {
        std::string line;
        std::ifstream file;
        file.open(filepath);

        if(file.is_open()) {
                getline(file, line); // Check first line
                if(line != "OFF") {
                        std::cerr << "Bad file format." << std::endl;
                } else {
                        // Retrieve number of vertices, faces and edges
                        getline(file, line);
                        vector<std::string> infos = splitLine(trimLine(line));
                        nbVertices = stoi(infos[0]);
                        nbFaces = stoi(infos[1]);
                        nbEdges = stoi(infos[2]);

//                        std::cout << "Number of vertices : " << nbVertices << std::endl;
//                        std::cout << "Number of faces : " << nbFaces << std::endl;
//                        std::cout << "Number of edges : " << nbEdges << std::endl;

                        std::cout << "Loading vertices ..." << std::endl;
                        Point	pointBuffer;
                        Face	faceBuffer;
                        bool    firstFace = true;
                        // Read points and faces definition
                        while(getline(file, line)) {
                                vector<std::string> v = splitLine(trimLine(line));

                                // Check if line is a comment
                                if(line[0] == '#') {
                                        continue;
                                }


                                // If not, treat the line as
                                if(isVertex(line)) {    // vertex coords
                                    pointBuffer.setPosition(v[0], v[1], v[2]);
                                    points.push_back(pointBuffer);
                                } else {	// face coords
                                    if(firstFace) {
                                        std::cout << "\rLoading faces ..." << std::endl;
                                        firstFace = false;
                                    }
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
                std::cerr << "Couldn't open file at \"" << filepath << "\"." << std::endl;
        }

        file.close();
}

//Solid::Solid(const Solid &src)
//{

//}

Solid::~Solid() { }

vector<std::string> Solid::splitLine(std::string s) {
        std::stringstream stream;
        stream.str(s);
        std::vector<std::string> ret;
        std::string buffer;

        while(getline(stream, buffer, ' ')) {
                if(!buffer.empty()) {
                        ret.push_back(buffer);
                }
        }

        return ret;
}

std::string Solid::trimLine(std::string& s) {
        size_t f = s.find_first_not_of(' ');
        size_t l = s.find_last_not_of(' ');
        s = s.substr(f, l-f+1);

        return s;
}

double Solid::computeSurface() {
        double result = 0.f;

        for(Face f : faces) {
                result += f.computeSurface();
        }

        return result;
}

double Solid::computeSurfaceWithThreads(int nbThreads)
{
    cout << "Start " << nbThreads << " threads." << endl;

    double result = 0.f;

    std::vector<pthread_t>          threads(nbThreads);
    std::vector<std::deque<Face*>*> facesBunch;

    // Build sections for each thread
    int range = faces.size()/nbThreads;
    int last = 0;
    for(size_t i = 0; i < nbThreads; i++) {
        last = (i+1)*range-1;
        if(last+range >= faces.size() && faces.size()-last > 0) {
            last += faces.size()-last-1;
        }

        facesBunch.push_back(new std::deque<Face*>());
        size_t f = 0;
        for(size_t j = i*range; j <= last; j++) {
            facesBunch[i]->push_back(new Face());
            facesBunch[i]->at(f) = &faces.at(j);
            f++;
        }

    }

    // Start threads
    for(size_t i = 0; i < nbThreads; i++) {
        pthread_create(&threads[i], NULL, computeFaces, (void*)facesBunch[i]);
    }

    // Get results back and sum them
    void* r;
    double* res;
    for(pthread_t& t : threads) {
        pthread_join(t, &r);
        res = (double*)r;
        result += (*res);
    }

    return result;
}




const bool Solid::isVertex(std::string &s){
        if(s[0] == '-' || s[0] == '0' )
            return true;

        size_t i = 0;
        while(s[i] != ' '){
                if(s[i] == '.')
                        return true;
            i++;
        }

        return false;
}
