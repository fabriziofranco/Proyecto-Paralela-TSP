#include "parser.cpp"
#include "functions.cpp"

#include <queue>

const float INFT = MAXFLOAT;

void branch_bound(adj_t mt);


adj_t matrix = [];

int main(int argc, char *argv[]){
    //auto adjMt = buildAdjMatrix(atoi(argv[1]));
    auto adjMt = matrix;
    auto p = reduce_matrix(adjMt);

    vector<float> id{1,2,3,4,5};
    vector<float> dist1{ INFT, 10,17, 0,1};
    vector<float> dist2{ 12, INFT,11,2 ,0};
    vector<float> dist3{ 0, 3,INFT , 0,2};
    vector<float> dist4{ 15, 3,12, INFT,0};
    vector<float> dist5{ 11, 0, 0, 12,INFT};

    for(int i = 0; i< id.size(); i++){
        for(int j = 0; j< id.size(); j++){
            pair<int, float> p{id[i], };
            
        }
    }

    
    return 0;
}



void branch_bound(adj_t mt){
    auto temp = reduce_matrix(mt);
    float cost = temp.second;
    mt = temp.first;
    
    
    
}