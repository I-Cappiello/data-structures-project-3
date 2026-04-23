#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Reads a given csv file and outputs a 2D vector containing all cells
// NOTE: does not actually work with csv files, I convereted airports.csv to a txt file to work
vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;    // The 2D vector that stores cell data
    ifstream file(filename);        // Opens the file
    
    // Should the file not exist
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }
    
    bool first = true;      // If the first line is being parsed
    string line;            // Stores the current line
    while (getline(file, line)) {
        vector<string> row;     // Stores a row's cell strings
        stringstream ss(line);  // Allows us to read/write from a given line
        string cell;            // Stores cell string
        int i = 0;              // Increment
        while (getline(ss, cell, ',')) {
            // Skips over Origin_City and Destinitation_City
            if(first && (i==3||i == 4||i==5)){
                row.push_back(cell);
            }
            // Skips over Origin_City and Destinitation_City
            else if(i<2 || i > 5){
                row.push_back(cell);
            }
            // Saves the Destination State
            else if(i==5){
                row.push_back(cell.substr(1,2));
            }
            i++;
        }
        first=false;
        // Row vector passed to data
        data.push_back(row);
    }
    // Closes file and returns 2D vector
    file.close();
    return data;
}

// Returns whether or not an airport is isolated
bool isIsolatedAirport(const string& code) {
    return (code == "HNL" || code == "ITO" || code == "OGG" ||
            code == "ALW" || code == "EAT" || code == "YKM" ||
            code == "BRD" || code == "BJI" ||
            code == "BTR" || code == "AHN" || code == "MLU" ||
            code == "SGF" || code == "ACT" ||
            code == "GYY" || code == "MWA" ||
            code == "BIL" || code == "BTM" || code == "HLN" ||
            code == "GEG" || code == "GTF" || code == "MSO" ||
            code == "PVU" || code == "FTW");
}

// Filters function that removed disconnected airports 
vector<vector<string>> filterDisconnectedAirports(const vector<vector<string>>& data) {
    vector<vector<string>> filtered_data;
    filtered_data.push_back(data[0]);  // Keep header
    for(int i = 1; i < data.size(); i++){
        string origin = data[i][0];
        string dest = data[i][1];
        // Checks if both nodes are among the disconnected airports    
        if(!isIsolatedAirport(origin) && !isIsolatedAirport(dest)) {
            filtered_data.push_back(data[i]);
        }
    }
    return filtered_data;
}

// Finds a if a state abbreviation (string) is within a string vector and returns the index 
int find_state_index(vector<string> states, string state){
    // Iterates through the vector
    for(int j = 0; j < states.size();j++){
        if(states[j]==state){
            return j;
        }
    }
    // If no matching element is found
    return -1;
}

// Finds if an airport code (string) is within a 2D string vector and returns the inner index
int find_airport(vector<vector<string>> airports, string airport, int sindex){
    //Iterates through the nested vector
    for(int j = 0; j < airports[sindex].size();j++){
        if(airports[sindex][j]==airport){
            return j;
        }
    }
    // If no matching element is found
    return -1;
}

int main() {
    // Stores csv data as well as its size
    auto data = readCSV("airports.txt");
    
    // Cancels program if data is empty
    if(data.empty()){
        cout << "No data loaded.\n";
        return 0;
    }
    int numRows = data.size();
    int numCol = data[0].size();
    vector<vector<string>> airports;
    vector<string> states;
    
    // Initializes graph objects
    Graph g;
    Graph g_u;
    
    // Enters data into directed and undirected graphs g and g_u
    for(int i = 1; i < numRows;i++){
        // Adds a row's airports if not already present
        Vertex v1(data[i][0]);
        Vertex v2(data[i][1]);
        // Adds the state and airport to states and airports if not already present 
        int s_index = find_state_index(states, data[i][2]);
        if(s_index==-1){
            states.push_back(data[i][2]);
            s_index = find_state_index(states, data[i][2]);
            airports.push_back(vector<string>());
        }
        if(find_airport(airports,data[i][1],s_index)==-1){
            airports[s_index].push_back(data[i][1]);
        }
        // Inserts edges and vertices into the directed and undirected graphs
        g.insert_vertex(v1);
        g_u.insert_vertex(v1);
        g.insert_vertex(v2);
        g_u.insert_vertex(v2);
        g.add_edge(v1,v2,stoi(data[i][3]),stoi(data[i][4]));
        g_u.add_undirected_edge(v1,v2,stoi(data[i][3]),stoi(data[i][4]));
    }
    
    // Prints graph data
    //g.print();
    //g_u.print();
    
    // Finds the shortest path between two airports
    //g.shortestPath("IAD", "MIA"); 
    
    // Finds the shortest path from one airport to all connected airports within a state
    //g.shortestPathsToState("ATL","FL",states,airports);
    
    //Finds the shortest path between two airports with a certain number of stops between them
    //g.shortestPathWithStops("IAD", "MIA", 2);
    
    // Finds the number of direct flights to and from all airports
    // g.display_flight_connections();
    
    // Checks the connectivity of the graph and displays unnconnected airports
    // g_u.check_connectivity();
    
    //Minimum Spanning Tree with Prim's Method
    //g_u.prim_mst();
    
    //Minimum Spanning Tree with Kruskal's Method
    //g_u.Kruskal_MST();
    return 0;
    
}
