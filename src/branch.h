#ifndef BRANCH_H
#define BRANCH_H

#include <vector>
#include "functions.h"


struct Branch{
    vector<int> path;
    adj_t adjMT;
    float cost;
    int vertex; // last vertex
};

ostream& operator<<(ostream& os, const Branch& br)
{
    for (int v: br.path)  os << v << "\t";
    os << br.path[0] <<"\n" << "cost: " << br.cost << "\n";
    for (size_t i = 0; i < br.adjMT.size(); i++)
    {
        for (size_t j = 0; j < br.adjMT.size(); j++){
            os << br.adjMT[i][j].second << "\t";
        }
    }
    os << "\n";
    return os;
}

struct CompareBranch {
    bool operator()(Branch const& b1, Branch const& b2)
    {
        return b1.cost > b2.cost;
    }
};

#endif