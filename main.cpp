#include<iostream>
#include<string>

#include "utility.h"
#include "preprocessing.h"
#include "exploration.h"

using namespace std;

void showMenu()
{
    cout<<"\n1.Load Data\n";
    cout<<"2.Remove Null Values\n";
    cout<<"3.Remove Duplicates\n";
    cout<<"4.Sort Ascending\n";
    cout<<"5.Sort Descending\n";
    cout<<"6.Display Data\n";
    cout<<"7.Mean\n";
    cout<<"8.Median\n";
    cout<<"9.Minimum\n";
    cout<<"10.Maximum\n";
    cout<<"11.Variance\n";
    cout<<"12.Standard Deviation\n";
    cout<<"13.Range\n";
    cout<<"14.Frequency\n";
    cout<<"15.Q1\n";
    cout<<"16.Q3\n";
    cout<<"17.IQR\n";
    cout<<"18.Outliers\n";
    cout<<"0.Exit\n";
}

int main()
{
    int choice;
    string filename;

    while(true)
    {
        showMenu();
        cin>>choice;

        if(choice==0)
        {
            break;
        }
        else if(choice==1)
        {
            cin>>filename;
            loadData(filename);
        }
        else if(choice==2)
        {
            removeNullValues();
        }
        else if(choice==3)
        {
            removeDuplicates();
        }
        else if(choice==4)
        {
            sortAscending();
        }
        else if(choice==5)
        {
            sortDescending();
        }
        else if(choice==6)
        {
            printData();
        }
        else if(choice==7)
        {
            cout<<calculateMean()<<endl;
        }
        else if(choice==8)
        {
            cout<<calculateMedian()<<endl;
        }
        else if(choice==9)
        {
            cout<<calculateMin()<<endl;
        }
        else if(choice==10)
        {
            cout<<calculateMax()<<endl;
        }
        else if(choice==11)
        {
            cout<<calculateVariance()<<endl;
        }
        else if(choice==12)
        {
            cout<<calculateStandardDeviation()<<endl;
        }
        else if(choice==13)
        {
            cout<<calculateRange()<<endl;
        }
        else if(choice==14)
        {
            calculateFrequency();
        }
        else if(choice==15)
        {
            cout<<calculateQ1()<<endl;
        }
        else if(choice==16)
        {
            cout<<calculateQ3()<<endl;
        }
        else if(choice==17)
        {
            cout<<calculateIQR()<<endl;
        }
        else if(choice==18)
        {
            detectOutliers();
        }
    }
    return 0;
}
