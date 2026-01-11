#include<iostream>
#include<vector>
#include<cmath>

#include "utility.h"
#include "preprocessing.h"

using namespace std;

double calculateMean()
{
    if(g_data.size()==0)
    {
        return 0;
    }

    double sum=0;
    for(int i=0;i<g_data.size();i++)
    {
        sum+=g_data[i];
    }
    return sum/g_data.size();
}

double calculateMedian()
{
    if(g_data.size()==0)
    {
        return 0;
    }

    sortAscending();
    int n=g_data.size();

    if(n%2==0)
    {
        return (g_data[n/2-1]+g_data[n/2])/2;
    }
    else
    {
        return g_data[n/2];
    }
}

double calculateMin()
{
    if(g_data.size()==0)
    {
        return 0;
    }

    double min=g_data[0];
    for(int i=1;i<g_data.size();i++)
    {
        if(g_data[i]<min)
        {
            min=g_data[i];
        }
    }
    return min;
}

double calculateMax()
{
    if(g_data.size()==0)
    {
        return 0;
    }

    double max=g_data[0];
    for(int i=1;i<g_data.size();i++)
    {
        if(g_data[i]>max)
        {
            max=g_data[i];
        }
    }
    return max;
}

double calculateVariance()
{
    if(g_data.size()==0)
    {
        return 0;
    }

    double mean=calculateMean();
    double sum=0;

    for(int i=0;i<g_data.size();i++)
    {
        double diff=g_data[i]-mean;
        sum+=diff*diff;
    }
    return sum/g_data.size();
}

double calculateStandardDeviation()
{
    return sqrt(calculateVariance());
}

double calculateRange()
{
    if(g_data.size()==0)
    {
        return 0;
    }
    return calculateMax()-calculateMin();
}

void calculateFrequency()
{
    if(g_data.size()==0)
    {
        return;
    }

    sortAscending();

    double current=g_data[0];
    int count=1;

    for(int i=1;i<g_data.size();i++)
    {
        if(g_data[i]==current)
        {
            count++;
        }
        else
        {
            cout<<current<<" "<<count<<endl;
            current=g_data[i];
            count=1;
        }
    }
    cout<<current<<" "<<count<<endl;
}

double calculateCorrelation()
{
    int n;
    cin>>n;

    if(n<=1)
    {
        return 0;
    }

    vector<double> x(n),y(n);

    for(int i=0;i<n;i++)
    {
        cin>>x[i]>>y[i];
    }

    double sumX=0,sumY=0,sumXY=0,sumX2=0,sumY2=0;

    for(int i=0;i<n;i++)
    {
        sumX+=x[i];
        sumY+=y[i];
        sumXY+=x[i]*y[i];
        sumX2+=x[i]*x[i];
        sumY2+=y[i]*y[i];
    }

    double numerator=n*sumXY-sumX*sumY;
    double denominator=sqrt((n*sumX2-sumX*sumX)*(n*sumY2-sumY*sumY));

    if(denominator==0)
    {
        return 0;
    }
    return numerator/denominator;
}

double calculateQ1()
{
    if(g_data.size()==0)
    {
        return 0;
    }

    sortAscending();
    int n=g_data.size();
    int mid=n/2;

    if(mid%2==0)
    {
        return (g_data[mid/2-1]+g_data[mid/2])/2;
    }
    else
    {
        return g_data[mid/2];
    }
}

double calculateQ3()
{
    if(g_data.size()==0)
    {
        return 0;
    }

    sortAscending();
    int n=g_data.size();
    int mid=n/2;
    int start;

    if(n%2==0)
    {
        start=mid;
    }
    else
    {
        start=mid+1;
    }

    int len=n-start;

    if(len%2==0)
    {
        return (g_data[start+len/2-1]+g_data[start+len/2])/2;
    }
    else
    {
        return g_data[start+len/2];
    }
}

double calculateIQR()
{
    return calculateQ3()-calculateQ1();
}

void detectOutliers()
{
    if(g_data.size()==0)
    {
        return;
    }

    double q1=calculateQ1();
    double q3=calculateQ3();
    double iqr=calculateIQR();

    double lower=q1-1.5*iqr;
    double upper=q3+1.5*iqr;

    for(int i=0;i<g_data.size();i++)
    {
        if(g_data[i]<lower||g_data[i]>upper)
        {
            cout<<g_data[i]<<endl;
        }
    }
}
