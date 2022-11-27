#include "parser.cpp"
#include "functions.cpp"

#include <queue>

void branch_bound(adj_t mt);


adj_t matrix = [];

int main(int argc, char *argv[]){
    //auto adjMt = buildAdjMatrix(atoi(argv[1]));
    auto adjMt = matrix;
    auto p = reduce_matrix(adjMt);

    vector<int> id{1,2,3,4,5};
    vector<float> dist{ INFT, 10,17, 0,1,  12, INFT,11,2 ,0,   0, 3,INFT , 0,2,    15, 3,12, INFT,0,   11, 0, 0, 12,INFT};


    for(int i = 0; i< id.size(); i++){
        for(int j = (id.size()*id[i])-5; j< id.size()*id[i] ; j++){
            cout<< id[i];
            cout<< endl;
            cout<< dist[j];
            
            
        }
    }
        }
    }

    
    return 0;
}



void branch_bound(adj_t mt){
    auto temp = reduce_matrix(mt);
    float cost = temp.second;
    mt = temp.first;
    
    
    
}