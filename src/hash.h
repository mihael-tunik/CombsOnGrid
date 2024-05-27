#ifndef HASH_H
#define HASH_H

#include <vector>
#include <algorithm>
#include <string>
#include "utils.h"

using namespace std;

typedef __uint128_t hash_t;
hash_t unique_hash(vector <pair<int, int>> &items, int N);
string uint128_to_str(__uint128_t num);
string uint128_to_uuid(__uint128_t num);

#endif
