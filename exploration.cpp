#include<vector>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<map>
#include"../include/utility.h"
#include"../include/exploration.h"

using namespace std;

vector<double> cleanColumn(int col)
{
    vector<double> d;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size()&&!isnan(g_data[i][col]))
            d.push_back(g_data[i][col]);
    }
    return d;
}

double calculateMean(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.empty()) return 0;
    double sum=0;
    for(int i=0;i<(int)d.size();i++) sum+=d[i];
    return sum/d.size();
}

double calculateMedian(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.empty()) return 0;
    sort(d.begin(),d.end());
    if(d.size()%2==0)
        return (d[d.size()/2-1]+d[d.size()/2])/2.0;
    else
        return d[d.size()/2];
}

double calculateMode(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.empty()) return 0;
    map<double,int> freq;
    for(int i=0;i<(int)d.size();i++) freq[d[i]]++;
    double mode=d[0];
    int maxFreq=0;
    for(auto &p:freq)
    {
        if(p.second>maxFreq)
        {
            maxFreq=p.second;
            mode=p.first;
        }
    }
    return mode;
}

double calculateVariance(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.empty()) return 0;
    double mean=calculateMean(col);
    double sum=0;
    for(int i=0;i<(int)d.size();i++)
    {
        double diff=d[i]-mean;
        sum+=diff*diff;
    }
    return sum/d.size();
}

double calculateStandardDeviation(int col)
{
    return sqrt(calculateVariance(col));
}

double calculateMin(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.empty()) return 0;
    return *min_element(d.begin(),d.end());
}

double calculateMax(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.empty()) return 0;
    return *max_element(d.begin(),d.end());
}

double calculateQ1(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.size()<4) return 0;
    sort(d.begin(),d.end());
    int mid=d.size()/2;
    vector<double> lower(d.begin(),d.begin()+mid);
    if(lower.size()%2==0)
        return (lower[lower.size()/2-1]+lower[lower.size()/2])/2.0;
    else
        return lower[lower.size()/2];
}

double calculateQ3(int col)
{
    vector<double> d=cleanColumn(col);
    if(d.size()<4) return 0;
    sort(d.begin(),d.end());
    int mid=d.size()/2;
    int start=(d.size()%2==0)?mid:mid+1;
    vector<double> upper(d.begin()+start,d.end());
    if(upper.size()%2==0)
        return (upper[upper.size()/2-1]+upper[upper.size()/2])/2.0;
    else
        return upper[upper.size()/2];
}

double calculateIQR(int col)
{
    return calculateQ3(col)-calculateQ1(col);
}

void detectOutliers(int col)
{
    double q1=calculateQ1(col);
    double q3=calculateQ3(col);
    double iqr=calculateIQR(col);
    double low=q1-1.5*iqr;
    double high=q3+1.5*iqr;
    cout<<"IQR Fences: ["<<low<<", "<<high<<"]"<<endl;
    bool found=false;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size()&&!isnan(g_data[i][col]))
        {
            double v=g_data[i][col];
            if(v<low||v>high)
            {
                cout<<"  Row "<<i<<": "<<v<<endl;
                found=true;
            }
        }
    }
    if(!found) cout<<"  No outliers detected."<<endl;
}

double calculateCorrelation(int colX,int colY)
{
    vector<double> x,y;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(colX<(int)g_data[i].size()&&colY<(int)g_data[i].size()
            &&!isnan(g_data[i][colX])&&!isnan(g_data[i][colY]))
        {
            x.push_back(g_data[i][colX]);
            y.push_back(g_data[i][colY]);
        }
    }
    int n=x.size();
    if(n==0) return 0;
    double sumX=0,sumY=0,sumXY=0,sumX2=0,sumY2=0;
    for(int i=0;i<n;i++)
    {
        sumX+=x[i];
        sumY+=y[i];
        sumXY+=x[i]*y[i];
        sumX2+=x[i]*x[i];
        sumY2+=y[i]*y[i];
    }
    double num=n*sumXY-sumX*sumY;
    double den=sqrt((n*sumX2-sumX*sumX)*(n*sumY2-sumY*sumY));
    if(den==0) return 0;
    return num/den;
}