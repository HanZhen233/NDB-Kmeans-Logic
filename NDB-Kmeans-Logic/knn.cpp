#include "knn.h"
#include<algorithm>
#include"Distance.h"
using namespace std;

/*
	ʹ�÷�����
	EuclidDis dis(colLen);  //ͬ������ʹ��HammingDis dis(colLen);
	KNN knn(3,nDBs,labels); //labels��nDBsһһ��Ӧ
	knn.setDistance(&dis);
	map<string,string> testResult = knn.testData(testdata);
*/
KNN::KNN(int k, vector<NDB> nDBs, vector<string> labels)
{
	this->k = k;
	this->nDBs = nDBs;
	this->labels = labels;
}

//�ṩ�Ĳ��Խӿ�
map<string, string> KNN::testData(vector<string> testData) {
	//���Խ��
	map<string, string> testResult;

	//����ÿһ��testData,����getMaxFreqLabel��������ȡ��Ӧ��label,Ȼ����Ϊ�������
	for (int i = 0; i < testData.size(); i++) {
		testResult[testData[i]] = getMaxFreqLabel(testData[i]);
	}

	return testResult;
}

//��ȡnDB��dValue֮��ľ���
double KNN::disNdb(NDB nDB, string dValue)
{

	return this->distance->getDistance(nDB, dValue);
}

//��ȡdValue�Ĳ��Խ������������һ��label
string KNN::getMaxFreqLabel(string dValue)
{
	for (int i = 0; i < nDBs.size(); i++) {
		mapIndexDis[i] = this->disNdb(nDBs[i], dValue);
	}

	//��mapת��Ϊpair,�Ա�������
	vector<PAIR> vecIndexDis(mapIndexDis.begin(), mapIndexDis.end());

	//��������
	sort(vecIndexDis.begin(), vecIndexDis.end(), CmpByValue());

	//�Ծ��������k��Ԫ�ؽ������ͳ��
	map<string, int> labelCount;
	for (int i = 0; i < k; i++) {
		labelCount[labels[vecIndexDis[i].first]]++;
	}

	//��������������
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

