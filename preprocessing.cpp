#include<iostream>
#include<vector>
#include<cmath>
#include"../include/utility.h"
#include"../include/exploration.h"
#include"../include/preprocessing.h"

using namespace std;

void removeNullRows(int col)
{
    vector<vector<double>> clean;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size()&&!isnan(g_data[i][col]))
            clean.push_back(g_data[i]);
    }
    int removed=g_data.size()-clean.size();
    g_data=clean;
    cout<<removed<<" null row(s) removed from column "<<col<<"."<<endl;
}

void replaceNullWithMean(int col)
{
    double mean=calculateMean(col);
    int replaced=0;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size()&&isnan(g_data[i][col]))
        {
            g_data[i][col]=mean;
            replaced++;
        }
    }
    cout<<replaced<<" null value(s) replaced with mean ("<<mean<<") in column "<<col<<"."<<endl;
}

void removeDuplicateRows()
{
    vector<vector<double>> unique;
    for(int i=0;i<(int)g_data.size();i++)
    {
        bool found=false;
        for(int j=0;j<(int)unique.size();j++)
        {
            if(g_data[i]==unique[j]){found=true;break;}
        }
        if(!found) unique.push_back(g_data[i]);
    }
    int removed=g_data.size()-unique.size();
    g_data=unique;
    cout<<removed<<" duplicate row(s) removed."<<endl;
}

void minMaxNormalize(int col)
{
    double minVal=calculateMin(col);
    double maxVal=calculateMax(col);
    if(maxVal-minVal==0){cout<<"Cannot normalize: all values are equal."<<endl;return;}
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size()&&!isnan(g_data[i][col]))
            g_data[i][col]=(g_data[i][col]-minVal)/(maxVal-minVal);
    }
    cout<<"Min-Max normalization applied to column "<<col<<"."<<endl;
}

void zScoreNormalize(int col)
{
    double mean=calculateMean(col);
    double std=calculateStandardDeviation(col);
    if(std==0){cout<<"Cannot normalize: standard deviation is 0."<<endl;return;}
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size()&&!isnan(g_data[i][col]))
            g_data[i][col]=(g_data[i][col]-mean)/std;
    }
    cout<<"Z-Score normalization applied to column "<<col<<"."<<endl;
}