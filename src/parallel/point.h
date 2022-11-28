#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>

using namespace std;


using adj_t = vector<vector<pair<int,float>>>;


struct Point{
    const float INF = MAXFLOAT;
    int id,x,y;
    vector<pair<int,float>> adj;

    Point(int id, int x, int y){
        this->id = id;
        this->x = x;
        this->y = y;
    }

    void buildAdj(vector<Point> &points){
        for(int i = 0; i < points.size(); i++){
            if(points[i].id != this->id){
                float dist = sqrt(pow(points[i].x - this->x,2) + pow(points[i].y - this->y,2));
                adj.push_back(make_pair(points[i].id, dist));
            }
            else{
                adj.push_back(make_pair(points[i].id, Point::INF));
            }
        }
    }
};

#endif