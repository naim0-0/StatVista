#include<iostream>
#include<fstream>
#include<sstream>
#include<cctype>
#include "utility.h"

vector<double> g_data;

bool isNumeric(string value)
{
    if(value=="")
    {
        return false;
    }

    int dotCount=0;
    int start=0;

    if(value[0]=='-'||value[0]=='+')
    {
        start=1;
    }

    for(int i=start;i<value.length();i++)
    {
        if(value[i]=='.')
        {
            dotCount++;
            if(dotCount>1)
            {
                return false;
            }
        }
        else if(!isdigit(value[i]))
        {
            return false;
        }
    }
    return true;
}

void loadData(string filename)
{
    g_data.clear();

    ifstream file(filename.c_str());
    string line,value;

    if(!file)
    {
        cout<<"File not found\n";
        return;
    }

    while(getline(file,line))
    {
        stringstream ss(line);
        while(getline(ss,value,','))
        {
            if(value!="NA"&&value!="null"&&value!="")
            {
                if(isNumeric(value))
                {
                    g_data.push_back(stod(value));
                }
            }
        }
    }
    file.close();
}

void printData()
{
    for(int i=0;i<g_data.size();i++)
    {
        cout<<g_data[i]<<" ";
    }
    cout<<endl;
}

int dataSize()
{
    return g_data.size();
}
