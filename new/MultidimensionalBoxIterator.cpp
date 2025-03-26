#include <cstdio>
#include <vector>
#include <set>
#include <chrono>
#include <string>
#include <climits>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

typedef unsigned long long ull;

inline int rho(vector <int> &a, vector <int> &b){
    int m = -1;
    for(int i = 0; i < a.size(); ++i)
       m = max(m, abs(a[i] - b[i]));
    return m;
}

inline int minimum_dist(vector <vector <int>> &items, vector <int> &coords){
    int min_d = 1e9;
    for(auto t : items)
        min_d = min(min_d, rho(coords, t));
    return min_d;
}

class MultidimensionalBoxIterator{
    public:

    vector <int> dims;
    vector <int> p_dims;
    int r, size;
    vector <vector <int>> m_get_coords;

    MultidimensionalBoxIterator(vector <int> &dims, int r){
        this->dims = dims, this->r = r;
        this->size = dims.size();
        this->p_dims = vector <int> (this->size + 1, 1);

        for(int i = this->size - 1; i >= 0; --i)
            this->p_dims[i] = this->p_dims[i+1] * this->dims[i];

        int l = 0;
        while(l < this->p_dims[0])
            this->m_get_coords.push_back(get_coords(l++));
    }

    int get_number(vector <int> &coords){
        int pos = 0;
        for(int i = 0; i < coords.size(); ++i)
            pos += this->p_dims[i + 1] * coords[i];
        return pos;
    }

    vector <int> get_coords(int l){
        vector <int> coords;
        for(int i = 0; i < this->size; ++i)
            coords.push_back((l / this->p_dims[i + 1]) % this->dims[i]);
        return coords;
    }

    int place_next(vector <vector <int>> &items, int &l){
        int box_size = this->p_dims[0];

        while(l < box_size){
            vector <int> c = this->m_get_coords[l]; //this->get_coords(l);
            if(minimum_dist(items, c) >= this->r){
                items.push_back(c);
                return l;
            }
            ++l;
        }
        return -1;
    }

    void next_combination(vector <vector <int>> &items){
        int M = items.size();

        while(items.size() > 0){
            int l = this->get_number(items.back()) + 1;
            items.pop_back();

            int repeat = M - items.size();
            for (int k = 0; k < repeat; ++k)
                if((l = this->place_next(items, l)) < 0)
                    break;

            if(items.size() == M)
                break;
        }
    }

    ull run(int M){
        int l = 0;
        ull cnt = 0;
        vector <vector <int>> items;
        
        for(int k = 0; k < M; ++k)
            if((l = this->place_next(items, l)) < 0)
                return cnt;

        while(items.size() > 0)
            this->next_combination(items), ++cnt;
        return cnt;
    }
};

// this code is faster
ull iterate_combs(int n, int k){
    vector <int> c(k);
    ull cnt = 0;
    int i;

    for (i = 0; i < k; i++) c[i] = k - i;

    while(1){
        ++cnt;
        
        i = 0;
        if (c[i]++ < n) continue;

        for(; c[i] >= n - i;) if(++i >= k) return cnt;
        for (c[i]++; i != 0; i--) c[i-1] = c[i] + 1;
    }
    return cnt;
}

/*ull iterate_combs(int n, int k){
    vector <int> p(n);
    ull cnt = 0;

    for(int i = 0; i < n; ++i){ p[i] = (i < k); }

    do{
        ++cnt;
    }while(prev_permutation(p.begin(), p.end()));

    return cnt;
}*/

int main(void){
    vector <int> dims = {10, 8, 8};
    int r = 7, k = 5;
    auto m = MultidimensionalBoxIterator(dims, r);

    std::chrono::high_resolution_clock::time_point start, stop;

    start = chrono::high_resolution_clock::now();
    ull ans = m.run(k); 
    stop = chrono::high_resolution_clock::now();
    
    printf("Ready in %lf s.\n", chrono::duration<double, milli>(stop-start).count()/1000);

    /*start = chrono::high_resolution_clock::now();
    ull cnt = iterate_combs(m.p_dims[0], k); 
    stop = chrono::high_resolution_clock::now();
    
    printf("Ready in %lf s.\n", chrono::duration<double, milli>(stop-start).count()/1000);
    cout << ans << " " << cnt << endl;*/
    cout << ans << endl;
    return 0;
}
