#pragma once
#include"toBString.h"

typedef struct NDB {
	vector<vector<int>> nData;
}NDB;
extern vector<NDB> nDBs;

void toNDB();
int findType(double rnd);//���������ԭ�����෴�ĸ���
void findPos( vector<int> &v,int type, int a[],int len); //���������ݵ���Ŀ