#include "CalDistance.h"
#include <numeric>

/*
	countNum: 用于统计每一位的0，1个数
	参数nDB: 负数据库中的一个数据
	参数CountBits: 用于返回统计的结果（即为公式二中的n1和n2）
	参数ndbLen: 生成的二进制串的列长
*/
void countNum(NDB nDB, int **countBits, int ndbLen) {
	//获取数据库中的记录
	vector<vector<int>> nData = nDB.nData;

	//每条串生成负数据库的长度
	int N = nData.size();

	//初始化数组为0
	for (int i = 0; i < ndbLen; i++) {
		countBits[i][0] = 0;
		countBits[i][1] = 0;
	}

	/*
		进行统计
	*/
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K0; j++) {
			/*
				数据库从1~136计数
				countBits从0~135计数，所以使用temp变量进行更改
			*/
			if (nData[i][j] > 0) {
				/*
					nData[i][j]大于0表示该位为1
				*/
				int temp = nData[i][j]-1;
				countBits[temp][1]++;
			}
			else {
				/*
					nData[i][j]小于0表示该位为0
				*/
				int temp = -(nData[i][j] + 1);
				countBits[temp][0]++;
			}
		}
	}
}

/*
	countQ: 计算第三公式中的Q
	参数countBits: countNum函数得到的统计结果（对于某一条记录）
	参数i: 第i个属性（i从0开始计数）
	参数L: 属性对应的二进制串长度数组(colLen[i]为第i个属性的二进制长度)
	返回值：公式三中的Q参数
*/
double* countQ(int** countBits, int i, vector<int> colLen) {
	/*
		计算pdiff,即公式一
		注：将来要放到全局（重复计算耗费时间）
	*/
	double pDiff = 0.0;
	for (int i = 1; i <= K0; i++) {
		pDiff += P[i] * i;
	}
	pDiff = pDiff / K0;

	double pSame = 1 - pDiff;

	//用于表示某一位为0或1的概率
	double *p0 = new double[colLen[i]];
	double *p1 = new double[colLen[i]];
	
	double sum = 0.0;
	
	//n是该属性所占的二进制串对应的最大十进制整数值
	int n = pow(2.0, colLen[i]);

	//返回结果
	double *Q = (double *)malloc(n * sizeof(double));

	//初始化
	//注：memset优化
	for (int c = 0; c < n; c++) {
		Q[c] = 1.0;
	}

	//count 是二进制串前i个属性二进制串总长
	int count = 0;
	for (int k = 0; k < i; k++) {
		count = count + colLen[k];
	}

	/*
		计算原字符串为0和1的概率（即公式二）
		变量q0：每一位为0的概率
		变量q1：每一位为1的概率
	*/
	for (int j = 0; j < colLen[i]; j++)
	{
		int id = count + j;
		
		//注：源代码中这样写
		//p0[j] = pow(Qsame[j], countBits[id][0])*pow(Qdiff[j], countBits[id][1]) / (pow(Qsame[j], countBits[id][0])*pow(Qdiff[j], countBits[id][1]) + pow(Qsame[j], countBits[id][1])*pow(Qdiff[j], countBits[id][0]));
		//p1[j] = pow(Qdiff[j], countBits[id][0])*pow(Qsame[j], countBits[id][1]) / (pow(Qsame[j], countBits[id][0])*pow(Qdiff[j], countBits[id][1]) + pow(Qsame[j], countBits[id][1])*pow(Qdiff[j], countBits[id][0]));

		//我按照暂时的公式理解计算
		p0[j] = pow(pSame, countBits[id][0])*pow(pDiff, countBits[id][1]) / (pow(pSame, countBits[id][0])*pow(pDiff, countBits[id][1]) + pow(pSame, countBits[id][1])*pow(pDiff, countBits[id][0]));
		p1[j] = pow(pDiff, countBits[id][0])*pow(pSame, countBits[id][1]) / (pow(pSame, countBits[id][0])*pow(pDiff, countBits[id][1]) + pow(pSame, countBits[id][1])*pow(pDiff, countBits[id][0]));
	}


	/*
		计算0~2**n之间的每一个数对应的概率（即为公式三中的Q），n即为L[i]
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

	//申请完释放
	delete[] p1;
	delete[] p0;

	return Q;
}

/*
	计算欧式距离(between nDB and Dvalue)
	参数nDB:某条数据的负数据库
	参数Dvalue:原数据对应的十进制值
	参数colLen:数据中的每个属性对应的长度
*/
double EuclidDis_NDB(NDB nDB, vector<double> Dvalue, vector<int> colLen) {
	//计算一个数据所占的二进制位数
	int totalColLen = accumulate(colLen.begin(), colLen.end(), 0);

	/*
		动态建立二维数组，数组维度为(sum(colLen),2)
	*/
	int** countBits = new int*[totalColLen];
	for (int i = 0; i < totalColLen; ++i) {
		countBits[i] = new int[2];
	}

	//countBits会在countNum函数中计算
	countNum(nDB, countBits, totalColLen);

	/*
		属性从0开始计数
	*/
	double distance = 0.0;
	for (int i = 0; i < colLen.size(); i++) {
		//返回公式三中的Q参数
		double* Q = countQ(countBits, i, colLen);
		int n = pow(2.0, colLen[i]);

		/*
			计算公式三内根号下的具体一项
		*/
		double attrDis = 0.0;
		for (int j = 0; j < n; j++) {
			attrDis += pow((j - Dvalue[i]),2.0)*Q[j];
		}

		//公式三根号下的累加和
		distance += attrDis;

		//！一定要释放
		delete [] Q;
	}

	//公式三结果记得开方
	distance = sqrt(distance);
	return distance;
}

/*
	已给代码中的value函数
	参数nDB: 负数据库中的一个数据
	参数colLen: 负数据库中的属性的长度
	返回结果: nDB对应的每一个属性的十进制值
*/
double* NDBvalue(NDB nDB, vector<int> colLen) {
	//返回的结果
	double* DvaluePAttr = new double[colLen.size()];

	//计算一个数据所占的二进制位数
	int totalColLen = accumulate(colLen.begin(), colLen.end(), 0);

	/*
		动态建立二维数组，数组维度为(sum(colLen),2)
	*/
	int** countBits = new int*[totalColLen];
	for (int i = 0; i < totalColLen; ++i) {
		countBits[i] = new int[2];
	}

	//countBits会在countNum函数中计算
	countNum(nDB, countBits, totalColLen);

	/*
		计算每一个属性的值
	*/
	for (int i = 0; i < colLen.size(); i++) {
		//返回公式三中的Q参数
		double* Q = countQ(countBits, i, colLen);
		int n = pow(2.0, colLen[i]);

		double attrDis = 0.0;
		for (int j = 0; j < n; j++) {
			attrDis += j*Q[j];
		}

		//！一定要释放
		delete[] Q;

		DvaluePAttr[i] = attrDis;
	}

	return DvaluePAttr;

}