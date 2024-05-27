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

vector <vector <int>> make_field(vector <pair<int, int>> &items, int N, int pad){
    vector <vector <int>> res;
    //int pad = 2;
    
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

void log_items(vector <pair<int, int>> &items, int id, int format, int N, string &save_folder, int flag_verbose, int batch_size, int pad){
     char file_name[128]; // ./test/out_1M.txt
     //printf("%s\n", save_folder.c_str());
     char units[] = {0, 0};
     
     if(batch_size == 1e3)
         units[0] = 'K';
     else if(batch_size == 1e6)
         units[0] = 'M';     
     
     sprintf(file_name, "%s/out_%i%s.txt", save_folder.c_str(), id/batch_size, units);
     //sprintf(file_name, "out_%iM.txt", id/1000000);
     FILE * f = fopen(file_name, "a+");
     
     //fprintf(f, "Combination %i:\n", id);
     
     if(format == 0 || format == 1){     
         for(int i = 0; i < items.size(); ++i)
             fprintf(f, "%i %i ", items[i].first + pad, items[i].second + pad);
         fprintf(f, "\n");    
     }
     
     if(format == 0 || format == 2){
         vector <vector <int>> field = make_field(items, N, pad);
    
         for(int i = 0; i < field.size(); ++i){
             for(int j = 0; j < field[0].size(); ++j)
                fprintf(f, "%i ", field[i][j]);
             fprintf(f, "\n");
         }
         fprintf(f, "\n");    
     }     
     
     //fprintf(f, "\n");         
     fclose(f);
     
     /* placed inside log_items() */
     //if( flag_verbose && ((id % flag_verbose) == 0) )
     //    printf("%i combinations found\n", id);
     return;
}

void read_items_template(char *file_name, vector <pair<int, int>> &fixed_template){  
     FILE *f = fopen(file_name, "r");    
     int x, y;
             
     while(fscanf(f, "%i %i", &x, &y) != EOF)
          fixed_template.push_back(make_pair(x, y));
     fclose(f);
     return;
}

