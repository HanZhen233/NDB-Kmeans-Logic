#include"Distance.h"
#include<math.h>
EuclidDis::EuclidDis(vector<int> colLen)
{
	this->colLen = colLen;

	//公式一计算pdiff和qdiff
	pDiff = 0.0;
	for (int i = 1; i <= K0; i++) {
		pDiff += P[i] * i;
	}
	pDiff = pDiff / K0;
	pSame = 1 - pDiff;
}

void EuclidDis::countOneAndZero(map<int, int>& oneCount, map<int, int>& zeroCount)
{
	//获取数据库中的记录
	vector<vector<int>> nData = nDB.nData;

	/*
		进行统计
	*/
	for (int i = 0; i < nData.size(); i++) {
		for (int j = 0; j < K0; j++) {
			/*
				数据库从1~136计数
				countBits从0~135计数，所以使用temp变量进行更改
			*/
			if (nData[i][j] > 0) {
				/*
					nData[i][j]大于0表示该位为1
				*/
				int temp = nData[i][j] - 1;
				oneCount[temp]++;
			}
			else {
				/*
					nData[i][j]小于0表示该位为0
				*/
				int temp = -(nData[i][j] + 1);
				zeroCount[temp]++;
			}
		}
	}
}

/*
	第i个属性，从0开始计数
*/
double EuclidDis::getAttrDvalue(string s, int i) {
	/*
		这里可以将count提取到外面
	*/
	int count = 0;
	for (int j = 0; j < i-1; j++) {
		count += colLen[j];
	}

	double dValue = 0.0;
	for (int j = colLen[i] - 1; j >= 0; j--) {
		if (s[j] == '1') {
			dValue += pow(2.0, j);
		}
	}
	
	return dValue;
}

vector<double> EuclidDis::getParamQ(int i) {
	vector<double> p0(colLen[i]);
	vector<double> p1(colLen[i]);

	double sum = 0.0;

	//n是该属性所占的二进制串对应的最大十进制整数值
	int n = pow(2.0, colLen[i]);

	vector<double> Q(n,1.0);

	//count 是二进制串前i个属性二进制串总长
	/*
		这里可以将count提取到外面
	*/
	int count = 0;
	for (int k = 0; k < i; k++) {
		count = count + colLen[k];
	}

	for (int j = 0; j < colLen[i]; j++)
	{
		int id = count + j;

		//我按照暂时的公式理解计算
		p0[j] = pow(pSame, zeroCount[id])*pow(pDiff, oneCount[id]) / (pow(pSame, zeroCount[id])*pow(pDiff, oneCount[id]) + pow(pSame, oneCount[id])*pow(pDiff, zeroCount[id]));
		p1[j] = pow(pDiff, zeroCount[id])*pow(pSame, oneCount[id]) / (pow(pSame, zeroCount[id])*pow(pDiff, oneCount[id]) + pow(pSame, oneCount[id])*pow(pDiff, zeroCount[id]));
	}

	for (int a = 0; a < n; a++) {
		int k = a;
		for (int b = colLen[i] - 1; b >= 0; b--) {
			if (k >= pow(2.0, b)) {
				Q[a] = Q[a] * p1[colLen[i] - b - 1];
				k = k - pow(2.0, b);
			}
			else {
				Q[a] = Q[a] * p0[colLen[i] - b - 1];
			}
		}
	}

	return Q;
}

void EuclidDis::setNdb(NDB nDB) {
	this->nDB = nDB;
}

double EuclidDis::getDistance(NDB nDB, string dValue)
{
	//设置nDB, 以便于调用其他函数不用传参
	setNdb(nDB);

	//nDB和dValue之间的距离
	double distance = 0.0;

	//统计前进行清除
	oneCount.clear();
	zeroCount.clear();

	//公式二统计nDB中的0，1数量
	countOneAndZero(oneCount, zeroCount);

	//公式三计算距离
	for (int i = 0; i < colLen.size(); i++) {
		vector<double> Q = getParamQ(i);

		int n = pow(2.0, colLen[i]);

		/*
			计算公式三内根号下的具体一项
		*/
		double attrDis = 0.0;

		//获取这个属性对应的二进制串对应的十进制值
		double attrValue = getAttrDvalue(dValue, i);
		
		/*
			注：这里的时间复杂度非常高！
			例如：假如colLen里面数字分别位5，6，7，4
			则会计算:2^5 + 2^6 + 2^7 + 2^4次
		*/
		for (int j = 0; j < n; j++) {
			attrDis += pow((j - attrValue), 2.0)*Q[j];
		}

		//attrDis为一个属性之间的距离
		distance += attrDis;
	}

	//公式三结果记得开方
	distance = sqrt(distance);
	
	//返回distance结果
	return distance;
}

//将来实现HammingDis的接口
double HammingDis::getDistance(NDB nDB, string dValue)
{
	return 0.0;
}
