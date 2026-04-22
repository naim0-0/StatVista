#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include"../include/utility.h"

using namespace std;

vector<vector<double>> g_data;
vector<string> g_headers;
string g_currentFile;

void loadData(string filename)
{
    g_data.clear();
    g_headers.clear();
    g_currentFile=filename;
    ifstream file(filename);
    string line,cell;
    if(!file.is_open())
    {
        cout<<"Unable to open file: "<<filename<<endl;
        return;
    }
    if(getline(file,line))
    {
        stringstream ss(line);
        while(getline(ss,cell,','))
        {
            if(!cell.empty()&&cell.back()=='\r') cell.pop_back();
            g_headers.push_back(cell);
        }
    }
    while(getline(file,line))
    {
        vector<double> row;
        stringstream ss(line);
        while(getline(ss,cell,','))
        {
            if(!cell.empty()&&cell.back()=='\r') cell.pop_back();
            if(cell.empty())
                row.push_back(NAN);
            else
                row.push_back(stod(cell));
        }
        if(row.size()==g_headers.size())
            g_data.push_back(row);
    }
    file.close();
    cout<<"\nData loaded successfully from: "<<filename<<endl;
    cout<<"Rows: "<<g_data.size()<<"  |  Columns: "<<g_headers.size()<<endl;
    cout<<"Columns: ";
    for(int i=0;i<(int)g_headers.size();i++)
        cout<<"["<<i<<"] "<<g_headers[i]<<"  ";
    cout<<endl;
}

void saveData()
{
    if(g_currentFile.empty())
    {
        cout<<"No file loaded."<<endl;
        return;
    }
    ofstream file(g_currentFile);
    if(!file.is_open())
    {
        cout<<"Unable to save file."<<endl;
        return;
    }
    for(int i=0;i<(int)g_headers.size();i++)
    {
        file<<g_headers[i];
        if(i<(int)g_headers.size()-1) file<<",";
    }
    file<<endl;
    for(int i=0;i<(int)g_data.size();i++)
    {
        for(int j=0;j<(int)g_data[i].size();j++)
        {
            if(isnan(g_data[i][j]))
                file<<"";
            else
                file<<g_data[i][j];
            if(j<(int)g_data[i].size()-1) file<<",";
        }
        file<<endl;
    }
    file.close();
    cout<<"Data saved to: "<<g_currentFile<<endl;
}

void saveDataAs(string filename)
{
    g_currentFile=filename;
    saveData();
}

void printData()
{
    if(g_data.empty())
    {
        cout<<"No data loaded."<<endl;
        return;
    }
    cout<<endl;
    for(int i=0;i<(int)g_headers.size();i++)
        cout<<"["<<i<<"] "<<g_headers[i]<<"\t";
    cout<<endl;
    cout<<string(60,'-')<<endl;
    for(int i=0;i<(int)g_data.size();i++)
    {
        for(int j=0;j<(int)g_data[i].size();j++)
        {
            if(isnan(g_data[i][j]))
                cout<<"NULL\t";
            else
                cout<<g_data[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

int getRowCount()
{
    return g_data.size();
}

int getColumnCount()
{
    if(g_data.empty()) return 0;
    return g_data[0].size();
}

vector<double> getColumn(int col)
{
    vector<double> column;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size())
            column.push_back(g_data[i][col]);
    }
    return column;
}