#include "comb_gen.h"
#include "condition.h"
#include "hash.h"
#include "utils.h"

void CombGenerator::build(vector <pair<int, int>> &items){
    for(int i = 0; i < fixed_template.size(); ++i)
        items.push_back(fixed_template[i]);
}

void CombGenerator::remove(vector <pair<int, int>> &items){
    for(int i = 0; i < fixed_template.size(); ++i)
        items.pop_back();
}

int CombGenerator::min_dist(vector <pair<int, int>> &items, int i, int j){
   int min = 1e9, r;
   pair<int, int> coord = make_pair(i, j);
   
   // ?
   for(int k = 0; k < items.size(); ++k){
      r = rho(items[k], coord);
      if(r < min)
          min = r;
   }
       
   for(int k = 0; k < fixed_template.size(); ++k){
      r = rho(fixed_template[k], coord);
      if(r < min)
          min = r;
   }
   return min;
}

int CombGenerator::place_next(vector <pair<int, int>> &items, int &l)
{
    int r = r_param;
       
    while(l < N*N){
       int i = l / N, j = l % N;       
       if(min_dist(items, i, j) >= r){       
          items.push_back(make_pair(i, j));
          return 1;
       }
       ++l;
    }  
    return 0;
}

void CombGenerator::process(vector <pair<int, int>> &items,
                            set <unsigned long long> &h_values,
                            unsigned long long *cnt, 
                            unsigned long long *saved_cnt)
{
    unsigned long long h_val;
    
    build(items);
            
    if(CC_condition(items, R_param)){
               
        h_val = unique_hash(items, N);                
                             
        /* val is unique */                      
        if(h_values.count(h_val) == 0){
            h_values.insert(h_val);

            if(flag_unique){
                (*saved_cnt)++; /* or h_values.size()? */
                log_items(items, *saved_cnt, format_output, N, save_folder, flag_verbose);
            }
                                                             
        }
        
        if(!flag_unique){
            (*saved_cnt)++;
            log_items(items, *saved_cnt, format_output, N, save_folder, flag_verbose);
            
            //if(flag_verbose && (*saved_cnt) % 10000 == 0)
            //    printf("%llu combinations found, %\n", *cnt);
        }         
   }
            
                       
   remove(items);
   (*cnt)++;
   
   return;
}


unsigned long long CombGenerator::combs_on_grid(){

    unsigned long long cnt = 0;
    unsigned long long saved_cnt = 0;
    
    vector <pair<int, int>> items;
    set <unsigned long long> h_values;   
            
    int l = 0;
    
    //printf("%s\n", this->save_folder.c_str());
        
    for(int i = 0; i < M; ++i)
        place_next(items, l);
        
    if(items.size() != M)
        return 0;
    
    process(items, h_values, &cnt, &saved_cnt);
           
    while(items.size()){
                    
        while(items.size() > 0){
          int i_ = items[items.size()-1].first, j_ = items[items.size()-1].second;
          l = N*i_ + j_ + 1;    
          
          items.pop_back();
          
          int flag = 1;
          
          for(int i = items.size(); i < M; ++i)
            if(place_next(items, l) == 0){
                flag = 0;
                break;
            }
                
          if(flag == 1)
             break;       
        }
        
        if(items.size())
            process(items, h_values, &cnt, &saved_cnt);
    }
    
    printf("OK: %llu, unique: %lu\n", cnt, h_values.size());
    return cnt;
}
