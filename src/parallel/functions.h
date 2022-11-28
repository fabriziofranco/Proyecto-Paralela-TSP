#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <omp>
#include <vector>
#include "point.h"

using namespace std;

const float INFT = MAXFLOAT;

float min_row(adj_t &mt, int row){
    float min = INFT;
    #omp parallel for private(i, min)
    for (auto p: mt[row]){
        if (p.second < min) min = p.second;
    }
    return min;   
}

float min_col(adj_t &mt, int col){
    float min = INFT;
    #omp parallel for private(i, min)
    for (size_t i = 0; i < mt[0].size(); i++)
    {
        if (mt[i][col].second < min) min = mt[i][col].second;
    }
    return min;   
}

pair<adj_t, float> reduce_matrix(adj_t &originalMatrix){

    auto rmatrix = originalMatrix;

    float cost = 0;
    
    #omp parallel for private(i, min_n, cost)
    for (size_t i = 0; i < rmatrix.size(); i++)
    {
        auto min_n = min_row(rmatrix, i);
        if (min_n!=0 && min_n != INFT) 
        {
            #omp parallel for private(j, min_n)
            for (size_t j = 0; j < rmatrix.size(); j++)
            {
                rmatrix[i][j].second -= min_n; 
            }  
            cost += min_n;
        }        
    }

    #omp parallel for private(i, min_n, cost)
    for (size_t i = 0; i < rmatrix.size(); i++)
    {
        auto min_n = min_col(rmatrix, i);
        if (min_n!=0 && min_n != INFT)
        {
            #omp parallel for private(j, min_n)
            for (size_t j = 0; j < rmatrix.size(); j++)
            {
                rmatrix[j][i].second -= min_n; 
            }  
            cost += min_n;
        }        
    }
    return make_pair(rmatrix, cost);
}

adj_t fill_INF(adj_t mt, int row, int col){

    #omp parallel for private(i)
    for (size_t i = 0; i < mt.size(); i++){
        mt[i][col].second = INFT;
        mt[row][i].second = INFT;
    }
    mt[col][row].second = INFT;
    return mt;
}

#endif