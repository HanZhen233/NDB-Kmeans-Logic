#include<iostream>
#include"infile.h"
#include"toBString.h"
#include"toNDB.h"
#include"calDistance.h"
#include"kmeans.h"
#include <numeric>
#include"Distance.h"
#include"knn.h"
using namespace std;

void knntest() {
	readDataWithLabel();

	for (int i = 0; i < dData.size(); i++)
	{
		for (int j = 0; j < dData[i].size(); j++)
		{
			cout << dData[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < labels.size(); i++) {
		cout << labels[i] << " ";
	}
	toBinaryString();
	for (int i = 0; i < colLen.size(); i++)
	{
		cout << colLen[i] << " ";
	}
	cout << endl;
	cout << bData[0] << endl;
	toNDB();

	for (int j = 0; j < nDBs[0].nData.size(); j++)
	{
		for (int i = 0; i < K0; i++)
		{
			cout << nDBs[0].nData[j][i] << "\t";
		}
		cout << endl;
	}

	for (int i = 0; i < bData.size(); i++) {
		cout << bData[i] << endl;
	}

	
}

int main() {
	knntest();
	
	EuclidDis dis(colLen);  //同样可以使用HammingDis dis(colLen);
	KNN knn(3, nDBs, labels); //labels和nDBs一一对应
	knn.setDistance(&dis);
	map<string, string> testResult = knn.testData(bData);
	cout << "end" << endl;
	/*srand((unsigned)time(NULL));
	readData();
	for (int  i = 0; i < dData.size(); i++)
	{
		for (int  j = 0; j < dData[i].size(); j++)
		{
			cout << dData[i][j] << " ";
		}
		cout << endl;
	}
	toBinaryString();
	for (int i = 0; i < colLen.size(); i++)
	{
		cout << colLen[i]<<" ";
	}
	cout << endl;
	cout << bData[0]<<endl;
	toNDB();
	
	for (int  j = 0; j <  nDBs[0].nData.size(); j++)
	{
		for (int i = 0; i < K0; i++)
		{
			cout << nDBs[0].nData[j][i] << "\t";
		}
		cout << endl;
	}
	
	cout << nDBs[0].nData[0][K0-1]<<endl;
	cout << nDBs[1].nData[0][K0 - 1] << endl;
	*/
	//总列长，用于生成记录统计结果的数组
	//int totalColLen = accumulate(colLen.begin(), colLen.end(), 0);
	//int **test=new int*[totalColLen];
/*	for (int i = 0; i < totalColLen; i++) {
		test[i] = new int[2];
	}
	countNum(nDBs[0],test,totalColLen);
	
	for (int i = 0; i < totalColLen; i++) {
		cout << test[i][0] << " " << test[i][0] << endl;
	}

	cout << "------------------------" << endl;
	countNum(nDBs[1], test, totalColLen);


	for (int i = 0; i < totalColLen; i++) {
		cout << test[i][0] << " " << test[i][0] << endl;
	}*/

	//kmeans(nDBs, 100, 4, colLen);
	/*
	double *test = NDBvalue(nDBs[0], colLen);

	for (int i = 0; i < colLen.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;

	delete[] test;
	test = NDBvalue(nDBs[1], colLen);

	for (int i = 0; i < colLen.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;
	delete[] test;
	*/
}


