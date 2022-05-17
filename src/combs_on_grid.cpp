#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <bitset>
#include <iostream>
#include <set>

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
    int N = 10, M = 2, r_param = 2, R_param = 5;
    vector <pair <int, int>> fixed_template;
    
    if(argc > 1){
        file_name = argv[1];
        read_items_template(file_name, fixed_template);
    }
            
    if(fixed_template.size() == 0)
        printf("No template is provided.\n");
    
    CombGenerator gen = CombGenerator(N, M, r_param, R_param, fixed_template);
    
    /* optional */
    gen.flag_unique = 0;           
    gen.flag_verbose = 0;
    gen.format_output = 1;
    
    printf("Output params:\nunique = %i\nverbose = %i\nformat = %i\n", 
           gen.flag_unique, gen.flag_verbose, gen.format_output);
    
    gen.combs_on_grid();
                
    return 0;
}



