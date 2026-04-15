#include<iostream>
#include<cmath>
#include<vector>
#include "utility.h"

using namespace std;

void simpleLinearRegression(int xCol, int yCol)
{
    vector<double> x = getColumn(xCol);
    vector<double> y = getColumn(yCol);

    int n = x.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int count = 0;

    for(int i = 0; i < n; i++)
    {
        if(isnan(x[i]) || isnan(y[i]))
        {
            continue;
        }

        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
        count++;
    }

    if(count < 2)
    {
        cout << "Not enough data for regression\n";
        return;
    }

    double slope = (count * sumXY - sumX * sumY) / (count * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / count;

    cout << "Regression Equation:\n";
    cout << "Y = " << intercept << " + " << slope << "X\n";

    if(slope > 0)
    {
        cout << "Relationship: Positive (Y increases as X increases)\n";
    }
    else if(slope < 0)
    {
        cout << "Relationship: Negative (Y decreases as X increases)\n";
    }
    else
    {
        cout << "Relationship: No linear relation\n";
    }

    double rmse = 0;
    for(int i = 0; i < n; i++)
    {
        if(isnan(x[i]) || isnan(y[i]))
        {
            continue;
        }

        double yPred = intercept + slope * x[i];
        rmse += (y[i] - yPred) * (y[i] - yPred);
    }

    rmse = sqrt(rmse / count);
    cout << "RMSE: " << rmse << endl;
}

void multipleLinearRegression(vector<int> xCols, int yCol)
{
    int n = g_data.size();
    int p = xCols.size();
    
    // Collect clean data (rows without NaN)
    vector<vector<double>> X;
    vector<double> Y;
    
    for(int i = 0; i < n; i++)
    {
        bool hasNaN = false;
        
        // Check if y value is NaN
        if(yCol >= g_data[i].size() || isnan(g_data[i][yCol]))
        {
            hasNaN = true;
        }
        
        // Check if any x value is NaN
        for(int j = 0; j < p; j++)
        {
            if(xCols[j] >= g_data[i].size() || isnan(g_data[i][xCols[j]]))
            {
                hasNaN = true;
                break;
            }
        }
        
        if(!hasNaN)
        {
            vector<double> row;
            row.push_back(1.0); // Intercept term
            
            for(int j = 0; j < p; j++)
            {
                row.push_back(g_data[i][xCols[j]]);
            }
            
            X.push_back(row);
            Y.push_back(g_data[i][yCol]);
        }
    }
    
    int m = X.size();
    int cols = p + 1;
    
    if(m < cols)
    {
        cout << "Not enough data for multiple regression\n";
        return;
    }
    
    // Create X'X matrix
    vector<vector<double>> XtX(cols, vector<double>(cols, 0.0));
    
    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            for(int k = 0; k < m; k++)
            {
                XtX[i][j] += X[k][i] * X[k][j];
            }
        }
    }
    
    // Create X'Y vector
    vector<double> XtY(cols, 0.0);
    
    for(int i = 0; i < cols; i++)
    {
        for(int k = 0; k < m; k++)
        {
            XtY[i] += X[k][i] * Y[k];
        }
    }
    
    // Solve using Gaussian elimination
    vector<vector<double>> A(cols, vector<double>(cols + 1, 0.0));
    
    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            A[i][j] = XtX[i][j];
        }
        A[i][cols] = XtY[i];
    }
    
    // Forward elimination
    for(int i = 0; i < cols; i++)
    {
        // Find pivot
        int maxRow = i;
        for(int k = i + 1; k < cols; k++)
        {
            if(abs(A[k][i]) > abs(A[maxRow][i]))
            {
                maxRow = k;
            }
        }
        
        // Swap rows
        swap(A[i], A[maxRow]);
        
        // Make all rows below this one 0 in current column
        for(int k = i + 1; k < cols; k++)
        {
            double factor = A[k][i] / A[i][i];
            for(int j = i; j <= cols; j++)
            {
                A[k][j] -= factor * A[i][j];
            }
        }
    }
    
    // Back substitution
    vector<double> coefficients(cols);
    
    for(int i = cols - 1; i >= 0; i--)
    {
        coefficients[i] = A[i][cols];
        for(int j = i + 1; j < cols; j++)
        {
            coefficients[i] -= A[i][j] * coefficients[j];
        }
        coefficients[i] /= A[i][i];
    }
    
    // Display results
    cout << "Multiple Linear Regression Equation:\n";
    cout << "Y = " << coefficients[0];
    
    for(int i = 0; i < p; i++)
    {
        if(coefficients[i + 1] >= 0)
        {
            cout << " + " << coefficients[i + 1] << "*X" << xCols[i];
        }
        else
        {
            cout << " - " << abs(coefficients[i + 1]) << "*X" << xCols[i];
        }
    }
    cout << "\n\nCoefficients:\n";
    cout << "Intercept: " << coefficients[0] << "\n";
    for(int i = 0; i < p; i++)
    {
        cout << "X" << xCols[i] << ": " << coefficients[i + 1] << "\n";
    }
    
    // Calculate RMSE and R-squared
    double sumSquaredError = 0.0;
    double sumSquaredTotal = 0.0;
    double meanY = 0.0;
    
    for(int i = 0; i < m; i++)
    {
        meanY += Y[i];
    }
    meanY /= m;
    
    for(int i = 0; i < m; i++)
    {
        double yPred = coefficients[0];
        for(int j = 0; j < p; j++)
        {
            yPred += coefficients[j + 1] * X[i][j + 1];
        }
        
        sumSquaredError += (Y[i] - yPred) * (Y[i] - yPred);
        sumSquaredTotal += (Y[i] - meanY) * (Y[i] - meanY);
    }
    
    double rmse = sqrt(sumSquaredError / m);
    double rSquared = 1.0 - (sumSquaredError / sumSquaredTotal);
    
    cout << "\nModel Statistics:\n";
    cout << "RMSE: " << rmse << "\n";
    cout << "R-squared: " << rSquared << "\n";
    cout << "Sample size: " << m << "\n";
}