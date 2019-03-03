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
	//kNN算法中的k
	int k;
	
	//属性所占的长度
	//vector<int> colLen;
	
	//训练数据
	vector<NDB> nDBs;

	//暂时存储一个二进制字符串到负数据库的距离
	map<int, double> mapIndexDis;

	//存储lable出现的次数
	vector<string> labels;

	//距离对象
	Distance* distance;

public:
	//构造函数
	KNN(int k, vector<NDB> nDBs, vector<string> labels);

	//计算距离
	double disNdb(NDB nDB, string dValue);

	//返回dValue对应的label
	string getMaxFreqLabel(string dValue);

	//设置计算什么样的距离
	void setDistance(Distance* distance);

	//比较辅助类，相当于java中的compara函数
	struct CmpByValue
	{
		bool operator() (const PAIR& lhs, const PAIR& rhs)
		{
			return lhs.second < rhs.second;
		}
	};

	//输入测试数据进行测试
	map<string, string> testData(vector<string> testData);
};