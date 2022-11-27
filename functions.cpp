#include <vector>
#include "point.cpp"

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
    for (size_t i = 0; i < mt.size(); i++)
    {
        if (mt[i][col].second < min) min = mt[i][col].second;
    }
    return min;   
}

pair<adj_t, float> reduce_matrix(adj_t &originalMatrix){

    auto rmatrix = originalMatrix;

    float cost = 0;
    
    for (size_t i = 0; i < rmatrix.size(); i++)
    {
        auto min_n = min_row(rmatrix, i);
        if (min_n!=0 || min_n != INFT) 
        {
            for (size_t j = 0; i < rmatrix[i].size(); j++)
            {
                rmatrix[i][j].second -= min_n; 
            }  
            cost += min_n;
        }        
    }

    for (size_t i = 0; i < rmatrix[0].size(); i++)
    {
        auto min_n = min_col(originalMatrix, i);
        if (min_n!=0 || min_n != INFT)
        {
            for (size_t j = 0; i < rmatrix.size(); j++)
            {
                rmatrix[j][i].second -= min_n; 
            }  
            cost += min_n;
        }        
    }
    return make_pair(rmatrix, cost);
}