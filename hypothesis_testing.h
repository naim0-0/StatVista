#ifndef HYPOTHESIS_TESTING_H
#define HYPOTHESIS_TESTING_H

#include<vector>
#include<string>

std::vector<std::string> splitLine(const std::string &line,char delimiter);
double z_valueFromTable(double value);
double t_valueFromTable(int dof,double alpha);
double chi_valueFromTable(double dof,double alpha);

void oneSided_Ztest(double null_hypothesis,double sigma,char sign);
void twoSided_Ztest(double null_hypothesis,double sigma);
void oneSided_Ttest(double null_hypothesis,char sign);
void twoSided_Ttest(double null_hypothesis);
void chi_Square_test(double null_hypothesis_variance);
void paired_Ttest();
void oneWayANOVA();

#endif