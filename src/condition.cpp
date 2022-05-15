#include "condition.h"

int CC_condition(vector <pair<int, int>> &items, int R){
    int items_size;
    vector <vector <int>> graph;
    
    items_size = items.size();            
    graph.resize(items_size);
    
    for(int k = 0; k < items_size; ++k){    
      for(int l = 0; l < items_size; ++l)
          if(l != k){
             int r = rho(items[k], items[l]);
             
             if(r <= R){
                 graph[l].push_back(k);
                 graph[k].push_back(l);
             }
          }
    }
                
    vector <int> g_stack, visited;
    
    visited.assign(items_size, 0);           
    g_stack.push_back(0);
    
    while(g_stack.size() != 0){
    
       int v = g_stack.back();
       
       visited[v] = 1;
       g_stack.pop_back();
       
       for(int i = 0; i < graph[v].size(); ++i)
           if(!visited[graph[v][i]])
               g_stack.push_back(graph[v][i]);
    }

    int check_sum = 0;
    
    for(int i = 0; i < visited.size(); ++i)
        check_sum += visited[i];

    return check_sum == items_size;
}

