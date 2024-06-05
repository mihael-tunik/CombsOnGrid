#ifndef COMB_GEN_H
#define COMB_GEN_H

#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <stdio.h>
#include "hash.h"

using namespace std;

class CombGenerator{
    public:
        int N, M, r_param, R_param;
        vector <pair <int, int>> fixed_template;

        int flag_unique, flag_verbose, format_output, flag_no_CC;
        int batch_size, snapshot_every;
        int pad = 0;
        
        string save_folder;
                 
    CombGenerator(int _N, int _M, int _r_param, int _R_param, vector <pair <int, int>> _fixed_template){
        N = _N;
        M = _M;
        r_param = _r_param;
        R_param = _R_param;
       
        fixed_template = _fixed_template;
        
        flag_unique = 1;
        flag_verbose = 1000;
        format_output = 0;
        flag_no_CC = 0;
        
        batch_size = 1000000;   
        snapshot_every = 100000;        
    }
    
    unsigned long long combs_on_grid();    
    
    void build(vector <pair<int, int>> &items);
    void remove(vector <pair<int, int>> &items);
    int min_dist(vector <pair<int, int>> &items, int i, int j);
    int place_next(vector <pair<int, int>> &items, int &l);
    
    hash_t process(vector <pair<int, int>> &items,
                 set <hash_t> &h_values,
                 unsigned long long *cnt, 
                 unsigned long long *saved_cnt);
                 
    hash_t process_fast(vector <pair<int, int>> &items,
                 unsigned long long *cnt, 
                 unsigned long long *saved_cnt);
                
    void make_snapshot(vector <pair<int, int>> &items, 
                       set <hash_t> &h_values, 
                       unsigned long long cnt,
                       unsigned long long saved_cnt,
                       hash_t h_val);
};

#endif
