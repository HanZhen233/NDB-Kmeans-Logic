#pragma once
#include<iostream>
#include<vector>
#include"toNDB.h"
using namespace std;
//��������
struct Cluster {
	//ĳһ��ľ�������
	vector<double> centroid;
	//��һ�������
	vector<int> samples;
};
vector<Cluster> kmeans(vector<NDB> nDBs, int iteration, int k, vector<int> colLen);