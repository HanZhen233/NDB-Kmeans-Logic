#pragma once
#include"toBString.h"

typedef struct NDB {
	vector<vector<int>> nData;
}NDB;
extern vector<NDB> nDBs;

void toNDB();
int findType(double rnd);//随机产生与原数据相反的个数
void findPos( vector<int> &v,int type, int a[],int len); //产生负数据的条目