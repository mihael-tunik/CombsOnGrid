#include <stdio.h>
#include <chrono>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <bitset>
#include <iostream>
#include <fstream>
#include <set>

#include <sys/stat.h>

#include "hash.h"
#include "utils.h"

using namespace std;

void read(vector <vector <pair<int, int>>> &batch, string filename, int M){
    ifstream f_in(filename.c_str());
    string line;
    
    while (std::getline(f_in, line)){
        const char *line_c_str = line.c_str();
        vector <pair <int, int>> comb;
        
        for(int i = 0; i < M; ++i){
            int x, y;
            sscanf(line_c_str, "%i %i", &x, &y);
            comb.push_back( make_pair(x, y) );
        }
        //printf("%s\n", line_c_str);
        batch.push_back(comb);
    }
    printf("Batch size of %i has been read.\n", batch.size());    
}

int main(int argc, char *argv[]){
    int N = 15, M = 7;
    set <hash_t> h_values;
    vector <string> files;
    string line;    
    
    ifstream f_reduce_list(argv[1]);
    
    while (std::getline(f_reduce_list, line)){
        files.push_back(line);
        printf("%s\n", line.c_str());
    }
    
    /*if(argc > 1){
        f_reduce_list = fopen(argv[1], "r");
        
    }*/
    
    auto start = chrono::high_resolution_clock::now();
    
    for(int i = 0; i < files.size(); ++i)
    {
        vector <vector <pair<int, int>>> batch;
        read(batch, files[i], M);
        
        for(int j = 0; j < batch.size(); ++j)
            h_values.insert(unique_hash(batch[j], N));
    }
    
    printf("Unique hashes: %i\n", h_values.size()); 
    //dump(h_values);
    
           
    auto stop = chrono::high_resolution_clock::now();
    printf("Ready in %lf s.\n", chrono::duration<double, milli>(stop-start).count()/1000);
               
    return 0;
}


