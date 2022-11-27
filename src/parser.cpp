#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>
#include "point.cpp"

using namespace std;

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


adj_t buildAdjMatrix(int N){
    string line;
    vector<string> lines;
    string path = "data/";
    ifstream myfile (path + to_string(N) + ".tsp");

    if (myfile.is_open()){
        for (int i=0; i<8; i++) getline(myfile, line);

        for (int i=0; i<N; i++){
            getline(myfile, line);
            lines.push_back(line);
        }

        myfile.close();

        vector<Point> points;
        for (int i = 0; i < lines.size(); i++){
            vector<string> point = split(lines[i], ' ');
            points.push_back(Point(atoi(point[0].c_str()),
                                   atoi(point[1].c_str()),
                                   atoi(point[2].c_str())));
        }

        adj_t adjMatrix;
        for (int i = 0; i < points.size(); i++){
            points[i].buildAdj(points);
            adjMatrix.push_back(points[i].adj);
        }
        return adjMatrix;
    }

    else{
        cout << "Unable to open file";
        return vector<vector<pair<int,float>>>();
    }
}
