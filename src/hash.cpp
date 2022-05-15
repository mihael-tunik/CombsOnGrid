#include "hash.h"

/* work with N^(2*M-1) */
unsigned long long hash_field(vector <pair<int, int>> &items, int N){
   
   vector <unsigned long long> powers;    
   unsigned long long Npow = 1, hash = 0;
   
   for(int i = 0; i < 2 * items.size(); ++i){
       powers.push_back(Npow);
       Npow *= N;
   }
   
   int min_x = N+1, min_y = N+1;
   
   for(int i = 0; i < items.size(); ++i)
   {
       if(items[i].first < min_x)
           min_x = items[i].first;
       
       if(items[i].second < min_y)
           min_y = items[i].second;
   }
   
   sort(items.begin(), items.end(), cmp);
                
   //min_x = 0, min_y = 0;
   
   for(int i = 0; i < items.size(); ++i){
       hash += (unsigned long long)(items[i].first - min_x) * powers[2*i];
       hash += (unsigned long long)(items[i].second - min_y) * powers[2*i+1];
   }
   
   return hash;                
}

void rotate(vector <pair<int, int>> &items, int N)
{
    for(int i = 0; i < items.size(); ++i){
        int x = items[i].first, y = items[i].second;        
        items[i] = make_pair(y, N-x-1);
    }
}

unsigned long long unique_hash(vector <pair<int, int>> &items, int N){

    vector <pair<int, int>> items_;
    vector <pair<int, int>> items_tr;
    
    vector <unsigned long long> hashes;
    unsigned long long min_h;
       
    for(int i = 0; i < items.size(); ++i){
        int x = items[i].first, y = items[i].second;
        
        items_tr.push_back(make_pair(y, x));
        items_.push_back(make_pair(x, y));
    }
        
    hashes.push_back( hash_field(items_, N) );
    hashes.push_back( hash_field(items_tr, N) );
        
    for(int k = 0; k < 3; ++k){       
        rotate(items_, N);
        rotate(items_tr, N);
        
        hashes.push_back( hash_field(items_, N) );
        hashes.push_back( hash_field(items_tr, N) );
    }
    
    min_h = hashes[0];
    
    for(int k = 1; k < hashes.size(); ++k)
        if(hashes[k] < min_h)
            min_h = hashes[k];
        
    return min_h;
}

