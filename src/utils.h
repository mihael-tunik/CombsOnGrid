#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

bool cmp(const pair <int, int> &a, const pair<int, int> &b);
int abs(int x);
int rho(pair<int, int> a, pair<int, int> b);
vector <vector <int>> make_field(vector <pair<int, int>> &items, int N);
void log_items(vector <pair<int, int>> &items, int id, int format, int N);
void read_items_template(char *file_name, vector <pair<int, int>> &fixed_template);

#endif
