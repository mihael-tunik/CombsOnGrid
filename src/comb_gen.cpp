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

unsigned long long CombGenerator::combs_on_grid(){

    unsigned long long cnt = 0, h_val;
    vector <pair<int, int>> items;
    set <unsigned long long> h_values;   
            
    int l = 0;
    
    for(int i = 0; i < M; ++i)
        place_next(items, l);
        
    if(items.size() != M)
        return 0;
    
    h_val = unique_hash(items, N);                                         
    h_values.insert(h_val);    
    cnt++;
           
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
        
        if(items.size()){
            
            build(items);
            
            if(CC_condition(items, R_param)){
                
                h_val = unique_hash(items, N);                
                                                   
                if(h_values.count(h_val) == 0){
                   h_values.insert(h_val);

                   //log_items(items, cnt);
                                                             
                   //if(cnt % 10000 == 0)
                   //   printf("%llu\n", cnt);
                }            
            }
            
            remove(items);            
            cnt++;                       
        }
    }
    
    printf("OK: %llu, unique: %lu\n", cnt, h_values.size());
    return cnt;
}

