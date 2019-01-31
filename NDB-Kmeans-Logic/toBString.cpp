#include"toBString.h"
vector<string> bData;
vector<int> colLen;
void toBinaryString() {
	int nCol = dData[0].size();
	int nRow = dData.size();
	int n = 0;//列长
	double MAX = 0.0,temp=0.0;	
	int MAX1 = 0,intTemp=0;
	//求每一列*100后转化成二进制串后能形成的最大长度，
	for (int j = 0; j < nCol; j++)
	{
		MAX = 0;
		for (int i = 0; i < nRow; i++)
		{
			dData[i][j] = dData[i][j] * AC;//消除小数点
			temp = fabs(dData[i][j]);// 求绝对值
			if (temp>MAX)
			{
				MAX = temp;//求绝对值最大值
			}

		}
		MAX1 = (int)(MAX);//强制转化成整数。
		cout << MAX << "\t";
		colLen.push_back ( findMaxBinaryLength(MAX1));//将该列的位数记录
	}
	cout << endl;
	/*根据列长按规则生成二进制串*/
	for (int i = 0; i < nRow; i++)
	{
		//string s="";
		stringstream ss;
		for (int j = 0; j < nCol; j++)
		{
			 n = colLen[j];
			 intTemp = (int)dData[i][j];
			for (int k =n-1 ; k >=0; k--)
			{
				//s +=itoa( (intTemp >> k) & 1);
				ss << ((intTemp >> k) & 1);
			}
		}
		string   s = ss.str();
		bData.push_back(s);
	}


}
//求出每一列的最大的位数。
int findMaxBinaryLength(int v) {
	int i=0;
	while (v>0)
	{
		v/= 2;
		i++;
	}
	return i;
}