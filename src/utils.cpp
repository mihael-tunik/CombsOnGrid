#include "utils.h"

bool cmp(const pair <int, int> &a, const pair<int, int> &b){
   if(a.first == b.first)
       return a.second < b.second;
   return a.first < b.first;
}

int abs(int x){
    return x >= 0 ? x : -x; 
}

int rho(pair<int, int> a, pair<int, int> b){
    int dx = abs(a.first-b.first), dy=abs(a.second-b.second);
    return (dx < dy) ? dy : dx;
}

vector <vector <int>> make_field(vector <pair<int, int>> &items, int N){
    vector <vector <int>> res;
    int pad = 2;
    
    res.resize(N + 2*pad);
        
    for(int i = 0; i < N + 2*pad; ++i)
        for(int j = 0; j < N + 2*pad; ++j)
            res[i].push_back(0);
            
    
    for(int i = 0; i < items.size(); ++i){
        int x = items[i].first, y = items[i].second;
        res[x+pad][y+pad] = 1;
    }
    
    return res;
}

void log_items(vector <pair<int, int>> &items, int id){
     char file_name[20];     
     sprintf(file_name, "out_%iM.txt", id/1000000);
     FILE * f = fopen(file_name, "a+");
     
     for(int i = 0; i < items.size(); ++i){
        int x = items[i].first, y = items[i].second;
        fprintf(f, "%i %i ", x, y);
     }
     fprintf(f, "\n");
     
     fclose(f);
     return;
}

void read_items_template(char *file_name, vector <pair<int, int>> &fixed_template){  
     FILE *f = fopen(file_name, "r");    
     int x, y;
             
     while(fscanf(f, "%i %i", &x, &y) != EOF)
          fixed_template.push_back(make_pair(x, y));
    
     //for(int i = 0; i < fixed_template.size(); ++i)
     //    printf("%i %i ", fixed_template[i].first, fixed_template[i].second);
          
     fclose(f);
     return;
}

