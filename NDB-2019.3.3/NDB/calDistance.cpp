#include "CalDistance.h"
#include <numeric>

/*
	countNum: ����ͳ��ÿһλ��0��1����
	����nDB: �����ݿ��е�һ������
	����CountBits: ���ڷ���ͳ�ƵĽ������Ϊ��ʽ���е�n1��n2��
	����ndbLen: ���ɵĶ����ƴ����г�
*/
void countNum(NDB nDB, int **countBits, int ndbLen) {
	//��ȡ���ݿ��еļ�¼
	vector<vector<int>> nData = nDB.nData;

	//ÿ�������ɸ����ݿ�ĳ���
	int N = nData.size();

	//��ʼ������Ϊ0
	for (int i = 0; i < ndbLen; i++) {
		countBits[i][0] = 0;
		countBits[i][1] = 0;
	}

	/*
		����ͳ��
	*/
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K0; j++) {
			/*
				���ݿ��1~136����
				countBits��0~135����������ʹ��temp�������и���
			*/
			if (nData[i][j] > 0) {
				/*
					nData[i][j]����0��ʾ��λΪ1
				*/
				int temp = nData[i][j]-1;
				countBits[temp][1]++;
			}
			else {
				/*
					nData[i][j]С��0��ʾ��λΪ0
				*/
				int temp = -(nData[i][j] + 1);
				countBits[temp][0]++;
			}
		}
	}
}

/*
	countQ: ���������ʽ�е�Q
	����countBits: countNum�����õ���ͳ�ƽ��������ĳһ����¼��
	����i: ��i�����ԣ�i��0��ʼ������
	����L: ���Զ�Ӧ�Ķ����ƴ���������(colLen[i]Ϊ��i�����ԵĶ����Ƴ���)
	����ֵ����ʽ���е�Q����
*/
double* countQ(int** countBits, int i, vector<int> colLen) {
	/*
		����pdiff,����ʽһ
		ע������Ҫ�ŵ�ȫ�֣��ظ�����ķ�ʱ�䣩
	*/
	double pDiff = 0.0;
	for (int i = 1; i <= K0; i++) {
		pDiff += P[i] * i;
	}
	pDiff = pDiff / K0;

	double pSame = 1 - pDiff;

	//���ڱ�ʾĳһλΪ0��1�ĸ���
	double *p0 = new double[colLen[i]];
	double *p1 = new double[colLen[i]];
	
	double sum = 0.0;
	
	//n�Ǹ�������ռ�Ķ����ƴ���Ӧ�����ʮ��������ֵ
	int n = pow(2.0, colLen[i]);

	//���ؽ��
	double *Q = (double *)malloc(n * sizeof(double));

	//��ʼ��
	//ע��memset�Ż�
	for (int c = 0; c < n; c++) {
		Q[c] = 1.0;
	}

	//count �Ƕ����ƴ�ǰi�����Զ����ƴ��ܳ�
	int count = 0;
	for (int k = 0; k < i; k++) {
		count = count + colLen[k];
	}

	/*
		����ԭ�ַ���Ϊ0��1�ĸ��ʣ�����ʽ����
		����q0��ÿһλΪ0�ĸ���
		����q1��ÿһλΪ1�ĸ���
	*/
	for (int j = 0; j < colLen[i]; j++)
	{
		int id = count + j;
		
		//ע��Դ����������д
		//p0[j] = pow(Qsame[j], countBits[id][0])*pow(Qdiff[j], countBits[id][1]) / (pow(Qsame[j], countBits[id][0])*pow(Qdiff[j], countBits[id][1]) + pow(Qsame[j], countBits[id][1])*pow(Qdiff[j], countBits[id][0]));
		//p1[j] = pow(Qdiff[j], countBits[id][0])*pow(Qsame[j], countBits[id][1]) / (pow(Qsame[j], countBits[id][0])*pow(Qdiff[j], countBits[id][1]) + pow(Qsame[j], countBits[id][1])*pow(Qdiff[j], countBits[id][0]));

		//�Ұ�����ʱ�Ĺ�ʽ������
		p0[j] = pow(pSame, countBits[id][0])*pow(pDiff, countBits[id][1]) / (pow(pSame, countBits[id][0])*pow(pDiff, countBits[id][1]) + pow(pSame, countBits[id][1])*pow(pDiff, countBits[id][0]));
		p1[j] = pow(pDiff, countBits[id][0])*pow(pSame, countBits[id][1]) / (pow(pSame, countBits[id][0])*pow(pDiff, countBits[id][1]) + pow(pSame, countBits[id][1])*pow(pDiff, countBits[id][0]));
	}


	/*
		����0~2**n֮���ÿһ������Ӧ�ĸ��ʣ���Ϊ��ʽ���е�Q����n��ΪL[i]
	*/
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

	//�������ͷ�
	delete[] p1;
	delete[] p0;

	return Q;
}

/*
	����ŷʽ����(between nDB and Dvalue)
	����nDB:ĳ�����ݵĸ����ݿ�
	����Dvalue:ԭ���ݶ�Ӧ��ʮ����ֵ
	����colLen:�����е�ÿ�����Զ�Ӧ�ĳ���
*/
double EuclidDis_NDB(NDB nDB, vector<double> Dvalue, vector<int> colLen) {
	//����һ��������ռ�Ķ�����λ��
	int totalColLen = accumulate(colLen.begin(), colLen.end(), 0);

	/*
		��̬������ά���飬����ά��Ϊ(sum(colLen),2)
	*/
	int** countBits = new int*[totalColLen];
	for (int i = 0; i < totalColLen; ++i) {
		countBits[i] = new int[2];
	}

	//countBits����countNum�����м���
	countNum(nDB, countBits, totalColLen);

	/*
		���Դ�0��ʼ����
	*/
	double distance = 0.0;
	for (int i = 0; i < colLen.size(); i++) {
		//���ع�ʽ���е�Q����
		double* Q = countQ(countBits, i, colLen);
		int n = pow(2.0, colLen[i]);

		/*
			���㹫ʽ���ڸ����µľ���һ��
		*/
		double attrDis = 0.0;
		for (int j = 0; j < n; j++) {
			attrDis += pow((j - Dvalue[i]),2.0)*Q[j];
		}

		//��ʽ�������µ��ۼӺ�
		distance += attrDis;

		//��һ��Ҫ�ͷ�
		delete [] Q;
	}

	//��ʽ������ǵÿ���
	distance = sqrt(distance);
	return distance;
}

/*
	�Ѹ������е�value����
	����nDB: �����ݿ��е�һ������
	����colLen: �����ݿ��е����Եĳ���
	���ؽ��: nDB��Ӧ��ÿһ�����Ե�ʮ����ֵ
*/
double* NDBvalue(NDB nDB, vector<int> colLen) {
	//���صĽ��
	double* DvaluePAttr = new double[colLen.size()];

	//����һ��������ռ�Ķ�����λ��
	int totalColLen = accumulate(colLen.begin(), colLen.end(), 0);

	/*
		��̬������ά���飬����ά��Ϊ(sum(colLen),2)
	*/
	int** countBits = new int*[totalColLen];
	for (int i = 0; i < totalColLen; ++i) {
		countBits[i] = new int[2];
	}

	//countBits����countNum�����м���
	countNum(nDB, countBits, totalColLen);

	/*
		����ÿһ�����Ե�ֵ
	*/
	for (int i = 0; i < colLen.size(); i++) {
		//���ع�ʽ���е�Q����
		double* Q = countQ(countBits, i, colLen);
		int n = pow(2.0, colLen[i]);

		double attrDis = 0.0;
		for (int j = 0; j < n; j++) {
			attrDis += j*Q[j];
		}

		//��һ��Ҫ�ͷ�
		delete[] Q;

		DvaluePAttr[i] = attrDis;
	}

	return DvaluePAttr;

}