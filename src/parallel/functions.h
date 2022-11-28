#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <omp.h>
#include <vector>
#include "point.h"

using namespace std;

const float INFT = MAXFLOAT;

float min_row(adj_t &mt, int row){
    float min = INFT;
    for (auto p: mt[row]){
        if (p.second < min) min = p.second;
    }
    return min;   
}

float min_col(adj_t &mt, int col){
    float min = INFT;
    for (size_t i = 0; i < mt[0].size(); i++)
    {
        if (mt[i][col].second < min) min = mt[i][col].second;
    }
    return min;   
}

pair<adj_t, float> reduce_matrix(adj_t &originalMatrix){

    auto rmatrix = originalMatrix;

    float cost = 0;
    
    #pragma omp parallel for
    for (size_t i = 0; i < rmatrix.size(); i++)
    {
        auto min_n = min_row(rmatrix, i);
        if (min_n != 0 && min_n != INFT) 
        {
            for (size_t j = 0; j < rmatrix.size(); j++)
            {
                #pragma omp atomic
                rmatrix[i][j].second -= min_n; 
            } 
            #pragma omp atomic
            cost += min_n;
        }        
    }

    #pragma omp parallel for
    for (size_t i = 0; i < rmatrix.size(); i++)
    {
        auto min_n = min_col(rmatrix, i);
        if (min_n!=0 && min_n != INFT)
        {
            for (size_t j = 0; j < rmatrix.size(); j++)
            {
                #pragma omp atomic
                rmatrix[j][i].second -= min_n; 
            }  
            #pragma omp atomic
            cost += min_n;
        }        
    }
    return make_pair(rmatrix, cost);
}

adj_t fill_INF(adj_t mt, int row, int col){

    #pragma omp parallel for
    for (size_t i = 0; i < mt.size(); i++){
        mt[i][col].second = INFT;
        mt[row][i].second = INFT;
    }
    mt[col][row].second = INFT;
    return mt;
}

#endif