#ifndef UTILITY_H
#define UTILITY_H

#include<vector>
#include<string>

using namespace std;

extern vector<double> g_data;

void loadData(string filename);
bool isNumeric(string value);
void printData();
int dataSize();

#endif
