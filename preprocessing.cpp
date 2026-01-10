#include<iostream>
#include<cmath>
#include<vector>

#include "utility.h"
#include "preprocessing.h"

using namespace std;

/* remove invalid numeric values */
void removeNullValues()
{
    vector<double> cleanData;

    for(int i=0;i<g_data.size();i++)
    {
        if(!std::isnan(g_data[i])&&!std::isinf(g_data[i]))
        {
            cleanData.push_back(g_data[i]);
        }
    }
    g_data=cleanData;
}

/* bubble sort ascending */
void sortAscending()
{
    int n=g_data.size();

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(g_data[j]>g_data[j+1])
            {
                double temp=g_data[j];
                g_data[j]=g_data[j+1];
                g_data[j+1]=temp;
            }
        }
    }
}

/* bubble sort descending */
void sortDescending()
{
    int n=g_data.size();

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(g_data[j]<g_data[j+1])
            {
                double temp=g_data[j];
                g_data[j]=g_data[j+1];
                g_data[j+1]=temp;
            }
        }
    }
}

/* remove duplicates (after sorting) */
void removeDuplicates()
{
    if(g_data.size()==0)
    {
        return;
    }

    sortAscending();

    vector<double> uniqueData;
    uniqueData.push_back(g_data[0]);

    for(int i=1;i<g_data.size();i++)
    {
        if(g_data[i]!=g_data[i-1])
        {
            uniqueData.push_back(g_data[i]);
        }
    }
    g_data=uniqueData;
}
