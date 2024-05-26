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
#include <map>
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
            int x, y, n;
            sscanf(line_c_str, "%i %i%n", &x, &y, &n);
            comb.push_back( make_pair(x, y) );
            //printf("%i %i\n", x, y);
            
            line_c_str += n;
        }
        
        //printf("%s\n", line_c_str);
        batch.push_back(comb);
    }
    
    //exit(0);
    printf("Batch size of %lu has been read.\n", batch.size());    
}

int main(int argc, char *argv[]){
    int N = 23, M = 7;
    set <hash_t> h_values;
    map < hash_t, vector < pair<int, int> > > h_values_combs;
    unsigned long long cnt = 0;
    
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
    
    printf("Found a list of %lu files\n", files.size());
    
    auto start = chrono::high_resolution_clock::now();
    
    for(int i = 0; i < files.size(); ++i)
    {
        vector <vector <pair<int, int>>> batch;
        read(batch, files[i], M);
        h_values_combs.clear(); //clean up, temporary solution 
        
        for(int j = 0; j < batch.size(); ++j){
            hash_t uh = unique_hash(batch[j], N);
            //printf("%s\n", uint128_to_str(uh).c_str());
            
            h_values_combs[uh] = batch[j];
            //h_values.insert(uh);
        }
        cnt += batch.size();
        double unique_r = (100.0 * h_values_combs.size()) / cnt;
        
        printf("File %s [%i/%lu], status: %llu processed, %lu found, %.3lf%% unique\n", 
            files[i].c_str(), i+1, files.size(), cnt, h_values_combs.size(), unique_r);
    }
    
    exit(0);
    printf("Unique hashes: %lu\n", h_values_combs.size()); 
    
    int id = 0, batch_size = 1000000;
    string save_folder("reducer_results");
    
    if (mkdir(save_folder.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
        printf("Failed to create folder for experiment.\n");
        return -1;
    }
        
    for (const auto& item : h_values_combs) {
        vector <pair<int, int>> comb = item.second;
        log_items(comb, id, 1, N, save_folder, 0, batch_size, 0);
        ++id;
        
        if(id > 0 && id % batch_size == 0)
            printf("%i combs saved.\n", id);
    }
                   
    auto stop = chrono::high_resolution_clock::now();
    printf("Ready in %lf s.\n", chrono::duration<double, milli>(stop-start).count()/1000);
               
    return 0;
}


