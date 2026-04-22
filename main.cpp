#include<iostream>
#include<string>
#include<vector>
#include"../include/utility.h"
#include"../include/preprocessing.h"
#include"../include/exploration.h"
#include"../include/regression.h"
#include"../include/hypothesis_testing.h"
#include"../include/plotting.h"

using namespace std;

static void showColumns()
{
    if(g_headers.empty()){cout<<"  (No data loaded)"<<endl;return;}
    cout<<"  Columns: ";
    for(int i=0;i<(int)g_headers.size();i++)
        cout<<"["<<i<<"] "<<g_headers[i]<<"  ";
    cout<<endl;
}

static int getCol(const string &prompt)
{
    int c;
    showColumns();
    cout<<"  "<<prompt;
    cin>>c;
    return c;
}

void menuPreprocessing()
{
    int choice;
    do {
        cout<<"\n+- Preprocessing ---------------------+"<<endl;
        cout<<"|  1. Remove Null Rows                |"<<endl;
        cout<<"|  2. Replace Null with Mean          |"<<endl;
        cout<<"|  3. Remove Duplicate Rows           |"<<endl;
        cout<<"|  4. Min-Max Normalize               |"<<endl;
        cout<<"|  5. Z-Score Normalize               |"<<endl;
        cout<<"|  0. Back                            |"<<endl;
        cout<<"+-------------------------------------+"<<endl;
        cout<<"  Choice: ";
        cin>>choice;
        int col;
        switch(choice)
        {
            case 1: col=getCol("Column index: ");removeNullRows(col);saveData();break;
            case 2: col=getCol("Column index: ");replaceNullWithMean(col);saveData();break;
            case 3: removeDuplicateRows();saveData();break;
            case 4: col=getCol("Column index: ");minMaxNormalize(col);saveData();break;
            case 5: col=getCol("Column index: ");zScoreNormalize(col);saveData();break;
            case 0: break;
            default: cout<<"  Invalid choice."<<endl;
        }
    } while(choice!=0);
}

void menuDescriptiveStats()
{
    int choice;
    do {
        cout<<"\n+- Descriptive Statistics ------------+"<<endl;
        cout<<"|  1.  Mean                           |"<<endl;
        cout<<"|  2.  Median                         |"<<endl;
        cout<<"|  3.  Mode                           |"<<endl;
        cout<<"|  4.  Variance                       |"<<endl;
        cout<<"|  5.  Standard Deviation             |"<<endl;
        cout<<"|  6.  Minimum                        |"<<endl;
        cout<<"|  7.  Maximum                        |"<<endl;
        cout<<"|  8.  Q1                             |"<<endl;
        cout<<"|  9.  Q3                             |"<<endl;
        cout<<"|  10. IQR                            |"<<endl;
        cout<<"|  11. Outliers                       |"<<endl;
        cout<<"|  12. Correlation (two columns)      |"<<endl;
        cout<<"|  0.  Back                           |"<<endl;
        cout<<"+-------------------------------------+"<<endl;
        cout<<"  Choice: ";
        cin>>choice;
        int col,colX,colY;
        switch(choice)
        {
            case 1:  col=getCol("Column index: ");cout<<"  Mean: "<<calculateMean(col)<<endl;break;
            case 2:  col=getCol("Column index: ");cout<<"  Median: "<<calculateMedian(col)<<endl;break;
            case 3:  col=getCol("Column index: ");cout<<"  Mode: "<<calculateMode(col)<<endl;break;
            case 4:  col=getCol("Column index: ");cout<<"  Variance: "<<calculateVariance(col)<<endl;break;
            case 5:  col=getCol("Column index: ");cout<<"  Std Dev: "<<calculateStandardDeviation(col)<<endl;break;
            case 6:  col=getCol("Column index: ");cout<<"  Min: "<<calculateMin(col)<<endl;break;
            case 7:  col=getCol("Column index: ");cout<<"  Max: "<<calculateMax(col)<<endl;break;
            case 8:  col=getCol("Column index: ");cout<<"  Q1: "<<calculateQ1(col)<<endl;break;
            case 9:  col=getCol("Column index: ");cout<<"  Q3: "<<calculateQ3(col)<<endl;break;
            case 10: col=getCol("Column index: ");cout<<"  IQR: "<<calculateIQR(col)<<endl;break;
            case 11: col=getCol("Column index: ");detectOutliers(col);break;
            case 12: showColumns();
                     cout<<"  X column: ";cin>>colX;
                     cout<<"  Y column: ";cin>>colY;
                     cout<<"  Correlation: "<<calculateCorrelation(colX,colY)<<endl;break;
            case 0:  break;
            default: cout<<"  Invalid choice."<<endl;
        }
    } while(choice!=0);
}

void menuZTest(const string &dataFile)
{
    int choice;
    cout<<"\n+- Z-Test ----------------------------+"<<endl;
    cout<<"|  1. One-Sided                       |"<<endl;
    cout<<"|  2. Two-Sided                       |"<<endl;
    cout<<"+-------------------------------------+"<<endl;
    cout<<"  Choice: ";
    cin>>choice;
    double mu0,sigma;
    char sign;
    if(choice==1)
    {
        cout<<"  Null hypothesis (mu0): ";cin>>mu0;
        cout<<"  Population sigma:      ";cin>>sigma;
        cout<<"  Direction (> or <):    ";cin>>sign;
        oneSided_Ztest(dataFile,mu0,sigma,sign);
    }
    else if(choice==2)
    {
        cout<<"  Null hypothesis (mu0): ";cin>>mu0;
        cout<<"  Population sigma:      ";cin>>sigma;
        twoSided_Ztest(dataFile,mu0,sigma);
    }
}

void menuTTest(const string &dataFile)
{
    int choice;
    cout<<"\n+- T-Test ----------------------------+"<<endl;
    cout<<"|  1. One-Sided                       |"<<endl;
    cout<<"|  2. Two-Sided                       |"<<endl;
    cout<<"+-------------------------------------+"<<endl;
    cout<<"  Choice: ";
    cin>>choice;
    double mu0;
    char sign;
    if(choice==1)
    {
        cout<<"  Null hypothesis (mu0): ";cin>>mu0;
        cout<<"  Direction (> or <):    ";cin>>sign;
        oneSided_Ttest(dataFile,mu0,sign);
    }
    else if(choice==2)
    {
        cout<<"  Null hypothesis (mu0): ";cin>>mu0;
        twoSided_Ttest(dataFile,mu0);
    }
}

void menuHypothesisTesting()
{
    int choice;
    do {
        cout<<"\n+- Hypothesis Testing ----------------+"<<endl;
        cout<<"|  1. Z-Test       (one-variable)     |"<<endl;
        cout<<"|  2. T-Test       (one-variable)     |"<<endl;
        cout<<"|  3. Chi-Square   (one-variable)     |"<<endl;
        cout<<"|  4. Paired T-Test (two-variable)    |"<<endl;
        cout<<"|  5. One-Way ANOVA                   |"<<endl;
        cout<<"|  0. Back                            |"<<endl;
        cout<<"+-------------------------------------+"<<endl;
        cout<<"  Choice: ";
        cin>>choice;
        string dataFile;
        double var0;
        switch(choice)
        {
            case 1:
                cout<<"  Dataset file (.txt): ";cin>>dataFile;
                menuZTest(dataFile);
                break;
            case 2:
                cout<<"  Dataset file (.txt): ";cin>>dataFile;
                menuTTest(dataFile);
                break;
            case 3:
                cout<<"  Dataset file (.txt): ";cin>>dataFile;
                cout<<"  Null hypothesis variance (sigma0^2): ";cin>>var0;
                chi_Square_test(dataFile,var0);
                break;
            case 4:
                cout<<"  Dataset file (.txt): ";cin>>dataFile;
                paired_Ttest(dataFile);
                break;
            case 5:
                cout<<"  Dataset file (.txt): ";cin>>dataFile;
                oneWayANOVA(dataFile);
                break;
            case 0:
                break;
            default:
                cout<<"  Invalid choice."<<endl;
        }
    } while(choice!=0);
}

void menuRegression()
{
    int choice;
    do {
        cout<<"\n+- Regression Analysis ---------------+"<<endl;
        cout<<"|  1. Simple Linear Regression        |"<<endl;
        cout<<"|  2. Multiple Linear Regression      |"<<endl;
        cout<<"|  0. Back                            |"<<endl;
        cout<<"+-------------------------------------+"<<endl;
        cout<<"  Choice: ";
        cin>>choice;
        int colX,colY,k;
        vector<int> xCols;
        switch(choice)
        {
            case 1:
                showColumns();
                cout<<"  X column: ";cin>>colX;
                cout<<"  Y column: ";cin>>colY;
                simpleLinearRegression(colX,colY);
                break;
            case 2:
                showColumns();
                cout<<"  Number of predictor columns: ";cin>>k;
                cout<<"  Enter "<<k<<" column indices: ";
                for(int i=0;i<k;i++){int c;cin>>c;xCols.push_back(c);}
                cout<<"  Target (Y) column: ";cin>>colY;
                multipleLinearRegression(xCols,colY);
                break;
            case 0: break;
            default: cout<<"  Invalid choice."<<endl;
        }
    } while(choice!=0);
}

void menuPlotting()
{
    int choice;
    do {
        cout<<"\n+- Plotting --------------------------+"<<endl;
        cout<<"|  1. Bar Chart (single column)       |"<<endl;
        cout<<"|  2. Scatter Plot (two columns)      |"<<endl;
        cout<<"|  0. Back                            |"<<endl;
        cout<<"+-------------------------------------+"<<endl;
        cout<<"  Choice: ";
        cin>>choice;
        int colX,colY;
        switch(choice)
        {
            case 1:
                colX=getCol("Column index: ");
                plotColumn(colX);
                break;
            case 2:
                showColumns();
                cout<<"  X column: ";cin>>colX;
                cout<<"  Y column: ";cin>>colY;
                plotScatter(colX,colY);
                break;
            case 0:
                break;
            default:
                cout<<"  Invalid choice."<<endl;
        }
    } while(choice!=0);
}

int main()
{
    int choice;
    string filename;
    cout<<"\n=========================================="<<endl;
    cout<<"                StatVista                  "<<endl;
    cout<<"        C++ Data Analysis Toolkit    "<<endl;
    cout<<"=========================================="<<endl;
    do {
        cout<<"\n+- Main Menu -------------------------+"<<endl;
        cout<<"|  1. Load Data                       |"<<endl;
        cout<<"|  2. Display Data                    |"<<endl;
        cout<<"|  3. Save Data                       |"<<endl;
        cout<<"|  4. Save Data As                    |"<<endl;
        cout<<"|  5. Preprocessing                   |"<<endl;
        cout<<"|  6. Descriptive Statistics          |"<<endl;
        cout<<"|  7. Hypothesis Testing              |"<<endl;
        cout<<"|  8. Regression Analysis             |"<<endl;
        cout<<"|  9. Plotting                        |"<<endl;
        cout<<"|  0. Exit                            |"<<endl;
        cout<<"+-------------------------------------+"<<endl;
        cout<<"  Choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1: cout<<"  Filename (e.g. data/sample.csv): ";cin>>filename;loadData(filename);break;
            case 2: printData();break;
            case 3: saveData();break;
            case 4: cout<<"  Save as filename: ";cin>>filename;saveDataAs(filename);break;
            case 5: menuPreprocessing();break;
            case 6: menuDescriptiveStats();break;
            case 7: menuHypothesisTesting();break;
            case 8: menuRegression();break;
            case 9: menuPlotting();break;
            case 0: cout<<"\n  Goodbye!\n"<<endl;break;
            default: cout<<"  Invalid choice."<<endl;
        }
    } while(choice!=0);
    return 0;
}