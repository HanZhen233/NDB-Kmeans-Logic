#include"toBString.h"
vector<string> bData;
vector<int> colLen;
void toBinaryString() {
	int nCol = dData[0].size();
	int nRow = dData.size();
	int n = 0;//�г�
	double MAX = 0.0,temp=0.0;	
	int MAX1 = 0,intTemp=0;
	//��ÿһ��*100��ת���ɶ����ƴ������γɵ���󳤶ȣ�
	for (int j = 0; j < nCol; j++)
	{
		MAX = 0;
		for (int i = 0; i < nRow; i++)
		{
			dData[i][j] = dData[i][j] * AC;//����С����
			temp = fabs(dData[i][j]);// �����ֵ
			if (temp>MAX)
			{
				MAX = temp;//�����ֵ���ֵ
			}

		}
		MAX1 = (int)(MAX);//ǿ��ת����������
		cout << MAX << "\t";
		colLen.push_back ( findMaxBinaryLength(MAX1));//�����е�λ����¼
	}
	cout << endl;
	/*�����г����������ɶ����ƴ�*/
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
//���ÿһ�е�����λ����
int findMaxBinaryLength(int v) {
	int i=0;
	while (v>0)
	{
		v/= 2;
		i++;
	}
	return i;
}