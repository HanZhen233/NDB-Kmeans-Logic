#pragma once
#include<iostream>
#include<vector>
#include"toNDB.h"
#include<string>
#include<map>
#include"Distance.h"
#include"global.h"
using namespace std;
typedef pair<int, double>  PAIR;
class KNN {
private:
	//kNN�㷨�е�k
	int k;
	
	//������ռ�ĳ���
	//vector<int> colLen;
	
	//ѵ������
	vector<NDB> nDBs;

	//��ʱ�洢һ���������ַ����������ݿ�ľ���
	map<int, double> mapIndexDis;

	//�洢lable���ֵĴ���
	vector<string> labels;

	//�������
	Distance* distance;

public:
	//���캯��
	KNN(int k, vector<NDB> nDBs, vector<string> labels);

	//�������
	double disNdb(NDB nDB, string dValue);

	//����dValue��Ӧ��label
	string getMaxFreqLabel(string dValue);

	//���ü���ʲô���ľ���
	void setDistance(Distance* distance);

	//�Ƚϸ����࣬�൱��java�е�compara����
	struct CmpByValue
	{
		bool operator() (const PAIR& lhs, const PAIR& rhs)
		{
			return lhs.second < rhs.second;
		}
	};

	//����������ݽ��в���
	map<string, string> testData(vector<string> testData);
};