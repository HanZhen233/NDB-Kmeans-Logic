#pragma once
#include<iostream>
#include"toNDB.h"
#include<map>
using namespace std;


class Distance {
public:
	virtual double getDistance(NDB nDB, string dValue) = 0;
};

class EuclidDis :public Distance {
private:
	vector<int> colLen;
	map<int, int> oneCount;
	map<int, int> zeroCount;
	double pDiff;
	double pSame;

	//NDBӦ�÷�װ��һ������Ȼ�������������в���
	NDB nDB;


public:
	EuclidDis(vector<int> colLen);
	void countOneAndZero(map<int, int>& oneCount, map<int, int>& zeroCount);
	double getAttrDvalue(string s, int i);
	vector<double> getParamQ(int i);
	void setNdb(NDB nDB);

	//�ṩ���ⲿ������õĽӿ�
	double getDistance(NDB nDB, string dValue);
};

class HammingDis :public Distance {
private:
	vector<int> colLen;
public:
	double getDistance(NDB nDB, string dValue);
};