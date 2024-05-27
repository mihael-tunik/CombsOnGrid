#include "hash.h"


string uint128_to_str(__uint128_t num)
{
    const char* charmap = "0123456789";
    string result;
    
    result.reserve( 40 );
    __uint128_t v = num;

    do {
        result += charmap[ v % 10 ];
        v /= 10;
    } while ( v != 0 );
    
    std::reverse( result.begin(), result.end() );
    return result;
}

string uint128_to_uuid(__uint128_t num)
{
    const char* charmap = "0123456789ABCDEF";
    string result;
    int base_hex = 16;
    
    result.reserve( 32 );
    __uint128_t v = num;

    for(int i = 0; i < 32; ++i){
        result += charmap[ v % base_hex ];
        v /= base_hex;
    }    
    std::reverse( result.begin(), result.end() );
    string middle = result.substr(8, 4) +  string("-") + result.substr(12, 4) + string("-") + result.substr(16, 4); 
    
    return result.substr(0, 8) + string("-") + middle + string("-") + result.substr(20, 12);
}
/*string uint128_to_str(__uint128_t num) {
    string str;
    do {
        int digit = num % 10;
        str = to_string(digit) + str;
        num = (num - digit) / 10;
    } while (num != 0);
    return str;
}*/

/* work with N^(2*M-1) */
hash_t hash_field(vector <pair<int, int>> &items, int N){
   
   vector <hash_t> powers;    
   hash_t Npow = 1, hash = 0, N_q = N;
   
   for(int i = 0; i < 2 * items.size(); ++i){
       powers.push_back(Npow);
       //printf("[%s]\n", uint128_to_str(Npow).c_str());       
       
       Npow *= N_q;
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
       hash_t hc, vc; // horizontal and vertical coords
       
       hc = items[i].first - min_x;
       vc = items[i].second - min_y;
       
       hash += hc * powers[2*i];
       hash += vc * powers[2*i+1];
       
       //printf("%s %s --->\n", uint128_to_str(hc).c_str(), uint128_to_str(vc).c_str());
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

hash_t unique_hash(vector <pair<int, int>> &items, int N){

    vector <pair<int, int>> items_;
    vector <pair<int, int>> items_tr;
    
    vector <hash_t> hashes;
    hash_t min_h;
    
    if(items.size() == 0){
       printf("Oooopsy ops.\n");
    }
       
    for(int i = 0; i < items.size(); ++i){
        int x = items[i].first, y = items[i].second;
        
        items_tr.push_back(make_pair(y, x));
        items_.push_back(make_pair(x, y));
    }
    
    // A B  C A  D C  B D
    // C D  D B  B A  A C
    
    // A C  B A  D B  C D
    // B D  D C  C A  A B
    
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


