# include"toNDB.h"
vector<NDB> nDBs;//�����ݿ�

void toNDB() {
	
	int m = bData[0].size();
	int *a=new int[m+1] ;
	int N = R*m;//ÿ�������ɸ����ݿ�ĳ���
	int type = 0,tmpPos;
	for (int i = 1; i <= m; i++)
	{
		a[i] = i;
	}    
	//��ÿ�������ƴ��������ɶ�Ӧ�����ݿ�
	for (int i = 0; i < bData.size(); i++)
	{
		NDB nDB;
		//��ÿ�������ƴ�����N�������ݿ��¼
		for (int j = 0; j < N; j++)
		{
			 double rnd= (rand()%100)*0.01;//�����
			// cout << rnd<<"\t";
			 type=findType(rnd);
			 vector<int> v;
			 findPos(v,type,a,m);
			 /*if (j==0|j==1)
			 {
				 cout << v[0]<<"\t"<<v[1] << "\t" <<v[2] << "\t" <<v[3] << endl;
			 }*/
			//�Ǹ�λ����ε��ڡ�0������-1��
			 //���λ�ñ���Ϊ��ֵ���÷�
			for (int  k = 0; k < K0; k++)
			 {
				 tmpPos = abs(v[k]);
				// cout << bData[i].at(tmpPos - 1) << "\t";
				 if ((bData[i].at(tmpPos-1) == '0'&v[k]<0)|| (bData[i].at(tmpPos - 1) == '0'&v[k]>0)) {
					 v[k] = -v[k];//0�÷�
				 }
				 else
				 {
					 v[k] = tmpPos;
				 }
			 }
			nDB.nData.push_back(v);//��Ӽ�¼
		}
		nDBs.push_back(nDB);
	}
}
//�������ÿ����¼������
int findType(double rnd) {
	for (int  i = 0; i <= K0; i++)
	{
		if (Q[i]>rnd)
		{
			return i;
		}
	}
}
//����ҵ�ȷ��λ��λ��
void findPos(vector<int> &v,int type , int a[],int len) {
	int m = bData[0].size();
	int rnd=0,flag=0,f=0;
	for (int i = len; i >len-K0; i--)
	{
		f++;
		swap(a[i], a[rand() % i+1]);
		if (f<=type)
		{
			v.push_back(-a[i]);
		}
		else
		{
			v.push_back(a[i]);
		}
	}
	
	/*
	while (v.size()<=K0)
	{
		rnd =rand() % m+1;//��1-m�������
		flag = 0;
		for (int  j = 0; j <v.size(); j++)
		{
			if (v[j]==rnd)
			{
				flag = 1;
				break;
			}
		}
		if (flag==0)
		{
			if (v.size()<=type)
			{
				rnd = -rnd;//�������ǰtype�����ȡ��
			}
			v.push_back(rnd);
		}
	}*/
}