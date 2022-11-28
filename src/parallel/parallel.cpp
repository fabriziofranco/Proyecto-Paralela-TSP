#include "parser.h"
#include "branch.h"
#include <chrono>

#include <omp.h>
#include <queue>

Branch branch_bound(adj_t mt);

int main(int argc, char *argv[]){
    omp_set_num_threads(2);
    string ws;
    cout<<"Desea correr el programa con los datos de demo? (s/n)"<<endl;
    cin>>ws;
    adj_t adjMt;

    if (ws == "N" or ws == "n"){
        int N=0;
        cout<<"Entonces, ingrese el ID de dataset: ";
        cin>>N;
        adjMt = buildAdjMatrix(N);
    }
    else if (ws == "S" or ws == "s"){
        vector<int> id{1,2,3,4,5};
        vector<vector<float>> dist{{ INFT, 20, 30, 10, 11},
                                    { 15, INFT, 16, 04, 02},
                                    { 03, 05, INFT, 02, 04},
                                    { 19, 06, 18, INFT, 03},
                                    { 16, 04, 07, 16, INFT}};    

        for(int i = 0; i< id.size(); i++){
            vector<pair<int, float>> row;
            for(int j = 0; j < id.size(); j++){
                row.push_back(make_pair(id[j], dist[i][j]));
            }
            adjMt.push_back(row);       
        }
    }
    else{
        cout << "Invalid argument";
        return 1;
    }
    auto start_time = chrono::high_resolution_clock::now();
    auto result = branch_bound(adjMt);
    auto end_time = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout<< "Min path: " << result;
    cout << "Time: " << time << " microseconds" << endl;
    return 0;
}



Branch branch_bound(adj_t mt){
    auto temp = reduce_matrix(mt);
    float cost = temp.second;
    cout << "Reduccion inicial: "<<cost << endl;
    mt = temp.first;
    
    priority_queue<Branch, vector<Branch>, CompareBranch> branches;
    auto current = Branch{{mt[0][0].first}, mt, cost};

    vector<Branch> possible_solutions;

    while (true){
        #pragma omp parallel for private(temp)
        for (int i = 0; i < mt.size(); i++){
            if (current.adjMT[current.vertex][i].second == INFT) continue;
            auto tadj = fill_INF(current.adjMT, current.vertex, i);
            temp = reduce_matrix(tadj);
            auto tpath = current.path;
            #pragma omp critical
            {
                tpath.push_back(mt[i][i].first);
                branches.push(Branch{tpath, temp.first, current.cost+temp.second+current.adjMT[current.vertex][i].second, i});
            }
        }

        current = branches.top();
        branches.pop();

        if (current.path.size() == mt.size()){
            possible_solutions.push_back(current);
            if (branches.top().cost < current.cost) continue;
            break;
        }
    }

    Branch min_branch = possible_solutions[0];
    #pragma omp parallel for private(min_branch)
    for(int i = 1; i < possible_solutions.size(); i++){
        if (possible_solutions[i].cost < min_branch.cost) {
            min_branch = possible_solutions[i];
        }
    }
    return current;
    
}