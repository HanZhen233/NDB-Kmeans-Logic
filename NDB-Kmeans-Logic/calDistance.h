#pragma once
#include"toNDB.h"
void countNum(NDB nDB, int **countBits, int ndbLen);
double* countQ(int** countBits, int i, vector<int> colLen);
double EuclidDis_NDB(NDB nDB, vector<double> Dvalue, vector<int> colLen);
double* NDBvalue(NDB nDB, vector<int> colLen);