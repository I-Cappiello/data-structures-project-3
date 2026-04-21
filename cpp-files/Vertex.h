#ifndef VERTEX_H
#define VERTEX_H

#include <string>
using namespace std;

class Vertex{
public:
    // Constructor
    Vertex(const string& d = string()) : data(d), visited(false) {};
    // Returns the data
    const string& getData() const {return data;}
    // Returns visited
    bool getVisited() const {return visited; }
    // Changes visited to parameter
    void setVisited(bool v) { visited = v; }

private:
    // Variables
    string data;    // Airport Code
    bool visited;   // Marks whether the node has been visited
};

#endif
