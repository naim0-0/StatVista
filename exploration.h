#ifndef EXPLORATION_H
#define EXPLORATION_H

#include<vector>

std::vector<double> cleanColumn(int col);
double calculateMean(int col);
double calculateMedian(int col);
double calculateMode(int col);
double calculateVariance(int col);
double calculateStandardDeviation(int col);
double calculateMin(int col);
double calculateMax(int col);
double calculateQ1(int col);
double calculateQ3(int col);
double calculateIQR(int col);
void detectOutliers(int col);
double calculateCorrelation(int colX,int colY);

#endif