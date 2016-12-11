#include "solid.h"

extern bool verbose;

void* computeFaces(void* data)
{
    double* r = new double(0.f);
    std::deque<Face*>* faces = (std::deque<Face*>*)data;
    for(size_t i = 0; i < faces->size(); i++) {
        (*r) += faces->at(i)->computeArea();
    }

    delete faces;

    return r;
}

Solid::Solid(std::string filePath) {
    std::string line;
    std::ifstream file;
    file.open(filePath);

    if(file.is_open()) {
        getline(file, line); // Check first line
        if(line != "OFF") {
                std::cerr << "Bad file format." << std::endl;
        } else {
            // Retrieve number of vertices, faces and edges
            getline(file, line);
            std::vector<std::string> infos = splitLine(trimLine(line));
            nbVertices = stoi(infos[0]);
            nbFaces = stoi(infos[1]);
            nbEdges = stoi(infos[2]);

            verbose && std::cout << "Loading vertices ..." << std::endl;
            Point	pointBuffer;
            Face	faceBuffer;
            bool    firstFace = true;
            unsigned i = 0;

            // Read points and faces definition
            while(getline(file, line)) {
                std::vector<std::string> v = splitLine(trimLine(line));

                // Check if line is a comment
                if(std::string("#").compare(v[0]) == 0) {
                    continue;
                }

                // If not, treat the line as
                if(i < nbVertices) {    // vertex coords
                    pointBuffer.setPosition(v[0], v[1], v[2]);
                    points.push_back(pointBuffer);
                } else {	// face coords
                    if(firstFace) {
                        verbose && std::cout << "\rLoading faces ..." << std::endl;
                        firstFace = false;
                    } else if(i-nbVertices > nbFaces) {
                        break;
                    }

                    size_t n = stoi(v[0]);
                    faceBuffer.clear();
                    faceBuffer.setVerticesNumber(n);
                    for (size_t i = n+1; i > 1; i--) {
                        faceBuffer.addVertex(&points[stoi(v[i-1])]);
                    }
                    faces.push_back(faceBuffer);
                }
                i++;
            }
        }
    } else {
            std::cerr << "Couldn't open file at \"" << filePath << "\"." << std::endl;
    }

    file.close();
}

Solid::~Solid() { }

std::vector<std::string> Solid::splitLine(std::string s) {
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
        result += f.computeArea();
    }

    return result;
}

double Solid::computeSurfaceWithThreads(unsigned nbThreads)
{
    double result = 0.f;

    // Build sections for each thread
    int range = faces.size()/nbThreads;
    if(range == 0) {
        range = 1;
        nbThreads = faces.size()-1;
    }
    int last = 0;

    std::vector<pthread_t>          threads(nbThreads);
    std::vector<std::deque<Face*>*> facesBunch;

    for(size_t i = 0; i < nbThreads; i++) {
        last = (i+1)*range-1;

        if(last+range >= faces.size() && faces.size()-last > 0) {
            last += faces.size()-last-1;
        }

        facesBunch.push_back(new std::deque<Face*>());
        size_t f = 0;
        for(size_t j = i*range; j <= last; j++) {
            facesBunch[i]->push_back(&faces.at(j));
            f++;
        }

    }

    // Start threads
    for(size_t i = 0; i < nbThreads; i++) {
        pthread_create(&threads[i], NULL, computeFaces, (void*)facesBunch[i]);
    }

    // Get results back and sum them
    void* r;
    for(pthread_t& t : threads) {
        double* res;

        pthread_join(t, &r);
        res = (double*)r;
        result += (*res);

        delete res;
    }

    return result;
}

double Solid::computeSurfaceWithOpenMP(){

    //Combined Parallel Loop Reduction
	#pragma omp parallel for reduction ( + : result )
    double result = 0.f;
    for(long i = 0; i < faces.size(); i++) {
        result += faces[i].computeArea();
    }

    return result;
}

const bool Solid::isVertex(std::string &s){
    if(s[0] == '-' || s[0] == '0' )
        return true;

	size_t i = 0;
    //Check if the first number is a float
    while(s[i] != ' '){
        if(s[i] == '.') return true;
        i++;
    }

    if(stoi(s) > 3)
        return true;

    return false;
}
