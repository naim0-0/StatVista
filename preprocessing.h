#ifndef PREPROCESSING_H
#define PREPROCESSING_H

void removeNullRows(int col);
void replaceNullWithMean(int col);
void removeDuplicateRows();
void minMaxNormalize(int col);
void zScoreNormalize(int col);

#endif