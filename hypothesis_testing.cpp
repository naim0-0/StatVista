#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<cmath>
#include"../include/hypothesis_testing.h"

using namespace std;

static const string Z_TABLE_FILE="data/Z_table.csv";
static const string T_TABLE_FILE="data/T_table.csv";
static const string CHI_TABLE_FILE="data/chi_square_table.csv";

vector<string> splitLine(const string &line,char delimiter)
{
    vector<string> result;
    stringstream ss(line);
    string token;
    while(getline(ss,token,delimiter))
    {
        result.push_back(token);
    }
    return result;
}

static vector<double> readOneVariable(const string &filename)
{
    vector<double> x;
    ifstream in(filename);
    if(!in)
    {
        cout<<"Cannot open "<<filename<<endl;
        return x;
    }
    double v;
    while(in>>v)
    {
        x.push_back(v);
    }
    in.close();
    return x;
}

static void readTwoVariable(const string &filename,vector<double> &x,vector<double> &y)
{
    ifstream in(filename);
    if(!in)
    {
        cout<<"Cannot open "<<filename<<endl;
        return;
    }
    double v1,v2;
    while(in>>v1>>v2)
    {
        x.push_back(v1);
        y.push_back(v2);
    }
    in.close();
}

static double calcMean(const vector<double> &v)
{
    double sum=0;
    for(double d:v)
    {
        sum+=d;
    }
    return sum/v.size();
}

static double calcDeviation(const vector<double> &v)
{
    double mean=calcMean(v);
    double sum=0;
    for(double d:v)
    {
        sum+=(d-mean)*(d-mean);
    }
    return sqrt(sum/(v.size()-1));
}

double z_valueFromTable(double value)
{
    value=floor(value*100)/100.0;
    ifstream file(Z_TABLE_FILE);
    if(!file.is_open())
    {
        cout<<"Cannot open "<<Z_TABLE_FILE<<endl;
        return -1;
    }
    vector<double> increments,baseValues;
    vector<vector<double>> table;
    string line;
    bool firstRow=true;
    while(getline(file,line))
    {
        vector<string> vals=splitLine(line,',');
        if(firstRow)
        {
            for(size_t i=1;i<vals.size();i++)
            {
                increments.push_back(stod(vals[i]));
            }
            firstRow=false;
        }
        else
        {
            baseValues.push_back(stod(vals[0]));
            vector<double> row;
            for(size_t i=1;i<vals.size();i++)
            {
                row.push_back(stod(vals[i]));
            }
            table.push_back(row);
        }
    }
    file.close();
    double baseZ=floor(value*10)/10.0;
    double inc=round((value-baseZ)*100)/100.0;
    double eps=1e-9;
    int rowIdx=-1,colIdx=-1;
    for(int i=0;i<(int)baseValues.size();i++)
    {
        if(fabs(baseValues[i]-baseZ)<eps)
        {
            rowIdx=i;
            break;
        }
    }
    for(int i=0;i<(int)increments.size();i++)
    {
        if(fabs(increments[i]-inc)<eps)
        {
            colIdx=i;
            break;
        }
    }
    if(rowIdx!=-1&&colIdx!=-1)
    {
        return table[rowIdx][colIdx];
    }
    cout<<"Z value not found in table."<<endl;
    return -1;
}

double t_valueFromTable(int dof,double alpha)
{
    ifstream file(T_TABLE_FILE);
    if(!file.is_open())
    {
        cout<<"Cannot open "<<T_TABLE_FILE<<endl;
        return -1;
    }
    vector<double> sigLevels;
    vector<int> dofs;
    vector<vector<double>> table;
    string line;
    bool firstRow=true;
    while(getline(file,line))
    {
        vector<string> vals=splitLine(line,',');
        if(firstRow)
        {
            for(size_t i=1;i<vals.size();i++)
            {
                sigLevels.push_back(stod(vals[i]));
            }
            firstRow=false;
        }
        else
        {
            dofs.push_back(stoi(vals[0]));
            vector<double> row;
            for(size_t i=1;i<vals.size();i++)
            {
                row.push_back(stod(vals[i]));
            }
            table.push_back(row);
        }
    }
    file.close();
    int rowIdx=-1,colIdx=-1;
    for(int i=0;i<(int)dofs.size();i++)
    {
        if(dofs[i]==dof)
        {
            rowIdx=i;
            break;
        }
    }
    for(int i=0;i<(int)sigLevels.size();i++)
    {
        if(fabs(sigLevels[i]-alpha)<1e-9)
        {
            colIdx=i;
            break;
        }
    }
    if(rowIdx!=-1&&colIdx!=-1)
    {
        return table[rowIdx][colIdx];
    }
    cout<<"T value not found (df="<<dof<<", alpha="<<alpha<<")."<<endl;
    return -1;
}

double chi_valueFromTable(double dof,double alpha)
{
    ifstream file(CHI_TABLE_FILE);
    if(!file.is_open())
    {
        cout<<"Cannot open "<<CHI_TABLE_FILE<<endl;
        return -1;
    }
    vector<double> sigLevels;
    vector<int> dofs;
    vector<vector<double>> table;
    string line;
    bool firstRow=true;
    while(getline(file,line))
    {
        vector<string> vals=splitLine(line,',');
        if(firstRow)
        {
            for(size_t i=1;i<vals.size();i++)
            {
                sigLevels.push_back(stod(vals[i]));
            }
            firstRow=false;
        }
        else
        {
            dofs.push_back(stoi(vals[0]));
            vector<double> row;
            for(size_t i=1;i<vals.size();i++)
            {
                row.push_back(stod(vals[i]));
            }
            table.push_back(row);
        }
    }
    file.close();
    int rowIdx=-1,colIdx=-1;
    for(int i=0;i<(int)dofs.size();i++)
    {
        if(dofs[i]==(int)dof)
        {
            rowIdx=i;
            break;
        }
    }
    for(int i=0;i<(int)sigLevels.size();i++)
    {
        if(fabs(sigLevels[i]-alpha)<1e-9)
        {
            colIdx=i;
            break;
        }
    }
    if(rowIdx!=-1&&colIdx!=-1)
    {
        return table[rowIdx][colIdx];
    }
    cout<<"Chi value not found (df="<<dof<<", alpha="<<alpha<<")."<<endl;
    return -1;
}

void oneSided_Ztest(const string &dataFile,double null_hypothesis,double sigma,char sign)
{
    vector<double> x=readOneVariable(dataFile);
    if(x.empty())
    {
        return;
    }
    double sample_mean=calcMean(x);
    int n=x.size();
    double z_stat=(sample_mean-null_hypothesis)/(sigma/sqrt(n));
    double alpha=0.05;
    double z_crit=z_valueFromTable(1.0-alpha);
    cout<<"\n--- One-Sided Z-Test ---"<<endl;
    cout<<"  Sample Mean:    "<<sample_mean<<endl;
    cout<<"  n:              "<<n<<endl;
    cout<<"  Z statistic:    "<<z_stat<<endl;
    cout<<"  Critical value: "<<z_crit<<" (alpha="<<alpha<<")"<<endl;
    bool reject=false;
    if(sign=='>'&&z_stat>z_crit)
    {
        reject=true;
    }
    if(sign=='<'&&z_stat<-z_crit)
    {
        reject=true;
    }
    if(reject)
    {
        cout<<"  Decision: REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
    else
    {
        cout<<"  Decision: FAIL TO REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
}

void twoSided_Ztest(const string &dataFile,double null_hypothesis,double sigma)
{
    vector<double> x=readOneVariable(dataFile);
    if(x.empty())
    {
        return;
    }
    double sample_mean=calcMean(x);
    int n=x.size();
    double z_stat=fabs((sample_mean-null_hypothesis)/(sigma/sqrt(n)));
    double alpha=0.05;
    double z_crit=z_valueFromTable(1.0-alpha/2.0);
    cout<<"\n--- Two-Sided Z-Test ---"<<endl;
    cout<<"  Sample Mean:    "<<sample_mean<<endl;
    cout<<"  n:              "<<n<<endl;
    cout<<"  |Z| statistic:  "<<z_stat<<endl;
    cout<<"  Critical value: "<<z_crit<<" (alpha/2="<<alpha/2.0<<")"<<endl;
    if(z_stat>z_crit)
    {
        cout<<"  Decision: REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
    else
    {
        cout<<"  Decision: FAIL TO REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
}

void oneSided_Ttest(const string &dataFile,double null_hypothesis,char sign)
{
    vector<double> x=readOneVariable(dataFile);
    if(x.empty())
    {
        return;
    }
    double sample_mean=calcMean(x);
    int n=x.size();
    double s=calcDeviation(x);
    double t_stat=(sample_mean-null_hypothesis)/(s/sqrt(n));
    double alpha=0.05;
    int dof=n-1;
    double t_crit=t_valueFromTable(dof,alpha);
    cout<<"\n--- One-Sided T-Test ---"<<endl;
    cout<<"  Sample Mean:    "<<sample_mean<<endl;
    cout<<"  Std Deviation:  "<<s<<endl;
    cout<<"  n:              "<<n<<"  (df="<<dof<<")"<<endl;
    cout<<"  T statistic:    "<<t_stat<<endl;
    cout<<"  Critical value: "<<t_crit<<" (alpha="<<alpha<<")"<<endl;
    bool reject=false;
    if(sign=='>'&&t_stat>t_crit)
    {
        reject=true;
    }
    if(sign=='<'&&t_stat<-t_crit)
    {
        reject=true;
    }
    if(reject)
    {
        cout<<"  Decision: REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
    else
    {
        cout<<"  Decision: FAIL TO REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
}

void twoSided_Ttest(const string &dataFile,double null_hypothesis)
{
    vector<double> x=readOneVariable(dataFile);
    if(x.empty())
    {
        return;
    }
    double sample_mean=calcMean(x);
    int n=x.size();
    double s=calcDeviation(x);
    double t_stat=fabs((sample_mean-null_hypothesis)/(s/sqrt(n)));
    double alpha=0.05;
    int dof=n-1;
    double t_crit=t_valueFromTable(dof,alpha/2.0);
    cout<<"\n--- Two-Sided T-Test ---"<<endl;
    cout<<"  Sample Mean:    "<<sample_mean<<endl;
    cout<<"  Std Deviation:  "<<s<<endl;
    cout<<"  n:              "<<n<<"  (df="<<dof<<")"<<endl;
    cout<<"  |T| statistic:  "<<t_stat<<endl;
    cout<<"  Critical value: "<<t_crit<<" (alpha/2="<<alpha/2.0<<")"<<endl;
    if(t_stat>t_crit)
    {
        cout<<"  Decision: REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
    else
    {
        cout<<"  Decision: FAIL TO REJECT H0 (mean = "<<null_hypothesis<<")"<<endl;
    }
}

void chi_Square_test(const string &dataFile,double null_hypothesis_variance)
{
    vector<double> x=readOneVariable(dataFile);
    if(x.empty())
    {
        return;
    }
    int n=x.size();
    double s=calcDeviation(x);
    double chi_stat=(n-1)*s*s/null_hypothesis_variance;
    double alpha=0.01;
    double dof=n-1;
    double lower=chi_valueFromTable(dof,1.0-alpha/2.0);
    double upper=chi_valueFromTable(dof,alpha/2.0);
    cout<<"\n--- Chi-Square Test (Variance) ---"<<endl;
    cout<<"  Sample Variance:    "<<s*s<<endl;
    cout<<"  n:                  "<<n<<"  (df="<<dof<<")"<<endl;
    cout<<"  Chi-Square stat:    "<<chi_stat<<endl;
    cout<<"  Acceptance region:  ["<<lower<<", "<<upper<<"]"<<endl;
    if(lower<chi_stat&&chi_stat<=upper)
    {
        cout<<"  Decision: FAIL TO REJECT H0 (variance = "<<null_hypothesis_variance<<")"<<endl;
    }
    else
    {
        cout<<"  Decision: REJECT H0 (variance = "<<null_hypothesis_variance<<")"<<endl;
    }
}

void paired_Ttest(const string &dataFile)
{
    vector<double> x,y;
    readTwoVariable(dataFile,x,y);
    if(x.empty()||y.empty())
    {
        return;
    }
    int n=min(x.size(),y.size());
    vector<double> d(n);
    for(int i=0;i<n;i++)
    {
        d[i]=x[i]-y[i];
    }
    double meanD=calcMean(d);
    double sD=calcDeviation(d);
    double t_stat=fabs(meanD/(sD/sqrt(n)));
    double alpha=0.05;
    int dof=n-1;
    double t_crit=t_valueFromTable(dof,alpha/2.0);
    cout<<"\n--- Paired T-Test ---"<<endl;
    cout<<"  Pairs (n):       "<<n<<endl;
    cout<<"  Mean difference: "<<meanD<<"  (X - Y per row)"<<endl;
    cout<<"  SD of diff:      "<<sD<<endl;
    cout<<"  df:              "<<dof<<endl;
    cout<<"  |T| statistic:   "<<t_stat<<endl;
    cout<<"  Critical value:  "<<t_crit<<"  (alpha/2="<<alpha/2.0<<")"<<endl;
    cout<<"\n  Pair differences:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"    Row "<<i<<": "<<x[i]<<" - "<<y[i]<<" = "<<d[i]<<endl;
    }
    cout<<endl;
    if(t_stat>t_crit)
    {
        cout<<"  Decision: REJECT H0 - significant difference between paired measurements."<<endl;
    }
    else
    {
        cout<<"  Decision: FAIL TO REJECT H0 - no significant difference between pairs."<<endl;
    }
}

void oneWayANOVA(const string &dataFile)
{
    ifstream in(dataFile);
    if(!in)
    {
        cout<<"Cannot open "<<dataFile<<endl;
        return;
    }
    vector<vector<double>> groups;
    string line;
    while(getline(in,line))
    {
        if(line.empty())
        {
            continue;
        }
        istringstream ss(line);
        double v;
        int idx=0;
        while(ss>>v)
        {
            if(idx>=(int)groups.size())
            {
                groups.resize(idx+1);
            }
            groups[idx].push_back(v);
            idx++;
        }
    }
    in.close();
    int k=groups.size();
    if(k<2)
    {
        cout<<"Need at least 2 groups for ANOVA."<<endl;
        return;
    }
    int N=0;
    for(int i=0;i<k;i++)
    {
        N+=groups[i].size();
    }
    double grandSum=0;
    for(int i=0;i<k;i++)
    {
        for(double v:groups[i])
        {
            grandSum+=v;
        }
    }
    double grandMean=grandSum/N;
    double SSB=0;
    for(int i=0;i<k;i++)
    {
        double gm=calcMean(groups[i]);
        SSB+=groups[i].size()*(gm-grandMean)*(gm-grandMean);
    }
    double SSW=0;
    for(int i=0;i<k;i++)
    {
        double gm=calcMean(groups[i]);
        for(double v:groups[i])
        {
            SSW+=(v-gm)*(v-gm);
        }
    }
    int dfB=k-1;
    int dfW=N-k;
    double MSB=SSB/dfB;
    double MSW=SSW/dfW;
    double F=MSB/MSW;
    double F_crit=2.87;
    cout<<"\n--- One-Way ANOVA ---"<<endl;
    cout<<"  Groups: "<<k<<"  |  Total observations: "<<N<<endl<<endl;
    cout<<"  Group Summaries:"<<endl;
    for(int i=0;i<k;i++)
    {
        double gm=calcMean(groups[i]);
        double gs=calcDeviation(groups[i]);
        cout<<"    Group "<<(i+1)<<":  n="<<groups[i].size()<<"  mean="<<gm<<"  sd="<<gs<<endl;
    }
    cout<<endl;
    cout<<"  ANOVA Table:"<<endl;
    cout<<"  Source      SS        df    MS        F"<<endl;
    cout<<"  -----------------------------------------"<<endl;
    cout<<"  Between     "<<SSB<<"\t  "<<dfB<<"     "<<MSB<<"\t  "<<F<<endl;
    cout<<"  Within      "<<SSW<<"\t  "<<dfW<<"     "<<MSW<<endl;
    cout<<"  Total       "<<SSB+SSW<<"\t  "<<N-1<<endl<<endl;
    cout<<"  F statistic:    "<<F<<endl;
    cout<<"  F critical:     "<<F_crit<<"  (df1="<<dfB<<", df2="<<dfW<<", alpha=0.05)"<<endl;
    if(F>F_crit)
    {
        cout<<"  Decision: REJECT H0 - significant difference among group means."<<endl;
    }
    else
    {
        cout<<"  Decision: FAIL TO REJECT H0 - no significant difference among group means."<<endl;
    }
}