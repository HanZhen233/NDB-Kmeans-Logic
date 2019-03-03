#pragma once
#include<iostream>
#include<vector>
#include"toNDB.h"
using namespace std;
//聚类中心
struct Cluster {
	//某一类的聚类中心
	vector<double> centroid;
	//这一类的样本
	vector<int> samples;
};
vector<Cluster> kmeans(vector<NDB> nDBs, int iteration, int k, vector<int> colLen);