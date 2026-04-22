#ifndef UTILITY_H
#define UTILITY_H

#include<vector>
#include<string>

extern std::vector<std::vector<double>> g_data;
extern std::vector<std::string> g_headers;
extern std::string g_currentFile;

void loadData(std::string filename);
void saveData();
void saveDataAs(std::string filename);
void printData();
int getRowCount();
int getColumnCount();
std::vector<double> getColumn(int col);

#endif