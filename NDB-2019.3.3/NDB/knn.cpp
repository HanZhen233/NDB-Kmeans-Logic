#include "knn.h"
#include<algorithm>
#include"Distance.h"
using namespace std;

/*
	使用方法：
	EuclidDis dis(colLen);  //同样可以使用HammingDis dis(colLen);
	KNN knn(3,nDBs,labels); //labels和nDBs一一对应
	knn.setDistance(&dis);
	map<string,string> testResult = knn.testData(testdata);
*/
KNN::KNN(int k, vector<NDB> nDBs, vector<string> labels)
{
	this->k = k;
	this->nDBs = nDBs;
	this->labels = labels;
}

//提供的测试接口
map<string, string> KNN::testData(vector<string> testData) {
	//测试结果
	map<string, string> testResult;

	//对于每一个testData,传入getMaxFreqLabel函数，获取对应的label,然后作为结果返回
	for (int i = 0; i < testData.size(); i++) {
		testResult[testData[i]] = getMaxFreqLabel(testData[i]);
	}

	return testResult;
}

//获取nDB和dValue之间的距离
double KNN::disNdb(NDB nDB, string dValue)
{

	return this->distance->getDistance(nDB, dValue);
}

//获取dValue的测试结果，即属于哪一个label
string KNN::getMaxFreqLabel(string dValue)
{
	for (int i = 0; i < nDBs.size(); i++) {
		mapIndexDis[i] = this->disNdb(nDBs[i], dValue);
	}

	//将map转化为pair,以便于排序
	vector<PAIR> vecIndexDis(mapIndexDis.begin(), mapIndexDis.end());

	//进行排序
	sort(vecIndexDis.begin(), vecIndexDis.end(), CmpByValue());

	//对距离最近的k个元素进行类别统计
	map<string, int> labelCount;
	for (int i = 0; i < k; i++) {
		labelCount[labels[vecIndexDis[i].first]]++;
	}

	//求得数量最大的类别
	map<string, int>::const_iterator mapIt = labelCount.begin();
	string finalLabel;
	int maxFreq = 0;
	
	while (mapIt != labelCount.end())
	{
		if (mapIt->second > maxFreq)
		{
			maxFreq = mapIt->second;
			finalLabel = mapIt->first;
		}
		mapIt++;
	}

	return finalLabel;
}

void KNN::setDistance(Distance * distance)
{
	this->distance = distance;
}

