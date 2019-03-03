# include"toNDB.h"
vector<NDB> nDBs;//负数据库

void toNDB() {
	
	int m = bData[0].size();
	int *a=new int[m+1] ;
	int N = R*m;//每条串生成负数据库的长度
	int type = 0,tmpPos;
	for (int i = 1; i <= m; i++)
	{
		a[i] = i;
	}    
	//对每条二进制串进行生成对应的数据库
	for (int i = 0; i < bData.size(); i++)
	{
		NDB nDB;
		//对每条二进制串生成N条负数据库记录
		for (int j = 0; j < N; j++)
		{
			 double rnd= (rand()%100)*0.01;//随机数
			// cout << rnd<<"\t";
			 type=findType(rnd);
			 vector<int> v;
			 findPos(v,type,a,m);
			 /*if (j==0|j==1)
			 {
				 cout << v[0]<<"\t"<<v[1] << "\t" <<v[2] << "\t" <<v[3] << endl;
			 }*/
			//那个位置如何等于‘0’的置-1，
			 //如果位置本身为负值则置反
			for (int  k = 0; k < K0; k++)
			 {
				 tmpPos = abs(v[k]);
				// cout << bData[i].at(tmpPos - 1) << "\t";
				 if ((bData[i].at(tmpPos-1) == '0'&v[k]<0)|| (bData[i].at(tmpPos - 1) == '0'&v[k]>0)) {
					 v[k] = -v[k];//0置反
				 }
				 else
				 {
					 v[k] = tmpPos;
				 }
			 }
			nDB.nData.push_back(v);//添加记录
		}
		nDBs.push_back(nDB);
	}
}
//随机产生每条记录的类型
int findType(double rnd) {
	for (int  i = 0; i <= K0; i++)
	{
		if (Q[i]>rnd)
		{
			return i;
		}
	}
}
//随机找到确定位的位置
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
		rnd =rand() % m+1;//从1-m的随机数
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
				rnd = -rnd;//随机数的前type个获得取反
			}
			v.push_back(rnd);
		}
	}*/
}