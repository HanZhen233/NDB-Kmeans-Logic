#include"Distance.h"
#include<math.h>
EuclidDis::EuclidDis(vector<int> colLen)
{
	this->colLen = colLen;

	//��ʽһ����pdiff��qdiff
	pDiff = 0.0;
	for (int i = 1; i <= K0; i++) {
		pDiff += P[i] * i;
	}
	pDiff = pDiff / K0;
	pSame = 1 - pDiff;
}

void EuclidDis::countOneAndZero(map<int, int>& oneCount, map<int, int>& zeroCount)
{
	//��ȡ���ݿ��еļ�¼
	vector<vector<int>> nData = nDB.nData;

	/*
		����ͳ��
	*/
	for (int i = 0; i < nData.size(); i++) {
		for (int j = 0; j < K0; j++) {
			/*
				���ݿ��1~136����
				countBits��0~135����������ʹ��temp�������и���
			*/
			if (nData[i][j] > 0) {
				/*
					nData[i][j]����0��ʾ��λΪ1
				*/
				int temp = nData[i][j] - 1;
				oneCount[temp]++;
			}
			else {
				/*
					nData[i][j]С��0��ʾ��λΪ0
				*/
				int temp = -(nData[i][j] + 1);
				zeroCount[temp]++;
			}
		}
	}
}

/*
	��i�����ԣ���0��ʼ����
*/
double EuclidDis::getAttrDvalue(string s, int i) {
	/*
		������Խ�count��ȡ������
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

	//n�Ǹ�������ռ�Ķ����ƴ���Ӧ�����ʮ��������ֵ
	int n = pow(2.0, colLen[i]);

	vector<double> Q(n,1.0);

	//count �Ƕ����ƴ�ǰi�����Զ����ƴ��ܳ�
	/*
		������Խ�count��ȡ������
	*/
	int count = 0;
	for (int k = 0; k < i; k++) {
		count = count + colLen[k];
	}

	for (int j = 0; j < colLen[i]; j++)
	{
		int id = count + j;

		//�Ұ�����ʱ�Ĺ�ʽ������
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
	//����nDB, �Ա��ڵ��������������ô���
	setNdb(nDB);

	//nDB��dValue֮��ľ���
	double distance = 0.0;

	//ͳ��ǰ�������
	oneCount.clear();
	zeroCount.clear();

	//��ʽ��ͳ��nDB�е�0��1����
	countOneAndZero(oneCount, zeroCount);

	//��ʽ���������
	for (int i = 0; i < colLen.size(); i++) {
		vector<double> Q = getParamQ(i);

		int n = pow(2.0, colLen[i]);

		/*
			���㹫ʽ���ڸ����µľ���һ��
		*/
		double attrDis = 0.0;

		//��ȡ������Զ�Ӧ�Ķ����ƴ���Ӧ��ʮ����ֵ
		double attrValue = getAttrDvalue(dValue, i);
		
		/*
			ע�������ʱ�临�Ӷȷǳ��ߣ�
			���磺����colLen�������ֱַ�λ5��6��7��4
			������:2^5 + 2^6 + 2^7 + 2^4��
		*/
		for (int j = 0; j < n; j++) {
			attrDis += pow((j - attrValue), 2.0)*Q[j];
		}

		//attrDisΪһ������֮��ľ���
		distance += attrDis;
	}

	//��ʽ������ǵÿ���
	distance = sqrt(distance);
	
	//����distance���
	return distance;
}

//����ʵ��HammingDis�Ľӿ�
double HammingDis::getDistance(NDB nDB, string dValue)
{
	return 0.0;
}
