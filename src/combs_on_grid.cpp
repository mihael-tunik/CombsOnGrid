#include <stdio.h>
#include <chrono>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <bitset>
#include <iostream>
#include <set>

#include <sys/stat.h>

#include "comb_gen.h"
#include "utils.h"

using namespace std;

int explicit_formula(int m, int n){
    switch(m){
        case 1:
            return n*n;
        case 2:
            return (n-1)*(n-2)*(n*n+3*n-2)/2;
        case 3:
            return (n-1)*(n-2)*(n*n*n*n+3*n*n*n-20*n*n-30*n+132)/6;       
    }
    return 0;
}

void tests_OEIS(){

    int passed = 0, failed = 0, res, ans;
    
    int r_param = 2, R_param = 100;
    vector <pair <int, int>> fixed_template;
    
    fixed_template.clear();
    
    CombGenerator gen = CombGenerator(1, 1, r_param, R_param, fixed_template);
    
    for(int M_test = 1; M_test <= 3; ++M_test)
    {
      printf("Tests for M=%i\n", M_test);
      
      for(int N_test = 3; N_test <= 12; ++N_test){
      
          gen.N = N_test, gen.M = M_test;
        
          res = gen.combs_on_grid();    
          ans = explicit_formula(M_test, N_test);
        
          printf("Res: %i, ans: %i\n", res, ans);
        
          if(res == ans)
             passed++;
          else
             failed++;
       }
    }       
    
    printf("Tests: %i passed, %i failed\n", passed, failed); 
}

int main(int argc, char *argv[]){
    char *file_name;
    int N = 23, M = 2, r_param = 3, R_param = 5;
    int flag_format_output = 1, flag_snapshot_every = 100000, flag_pad = 0;
    
    vector <pair <int, int>> fixed_template;
    
    if(argc > 1){
        file_name = argv[1];
        read_items_template(file_name, fixed_template);
        
        N = atoi(argv[2]);
        M = atoi(argv[3]);
        
        r_param = atoi(argv[4]);
        R_param = atoi(argv[5]);
        
        printf("(N, M, r, R) = %i %i %i %i\n", N, M, r_param, R_param);
        
        //flag_format_output = atoi(argv[7]);
        flag_pad = atoi(argv[7]);
    }
                
    if(fixed_template.size() == 0)
        printf("No template is provided.\n");
    else{
        printf("Template is provided:\n");
        for(int i = 0; i < fixed_template.size(); ++i)
            printf("%i %i\n", fixed_template[i].first, fixed_template[i].second);
    }
    
    CombGenerator gen = CombGenerator(N, M, r_param, R_param, fixed_template);

    gen.save_folder = string(argv[6]);
        
    if (mkdir(gen.save_folder.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
        gen.save_folder = string(".");
        printf("Failed to create folder for experiment.\n");
    }
    
    /* optional */
    gen.flag_unique    = 0;           
    gen.flag_verbose   = 100000;
    gen.format_output  = flag_format_output;    
    gen.batch_size     = 2000000000;
    gen.snapshot_every = flag_snapshot_every;
    gen.flag_no_CC     = 0;
    gen.pad            = flag_pad;
    
    printf("Output params:\nunique = %i\nverbose = %i\nformat = %i\n", 
           gen.flag_unique, gen.flag_verbose, gen.format_output);
    
    auto start = chrono::high_resolution_clock::now(); 
    gen.combs_on_grid();
    auto stop = chrono::high_resolution_clock::now();
    printf("Ready in %lf s.\n", chrono::duration<double, milli>(stop-start).count()/1000);
               
    return 0;
}



