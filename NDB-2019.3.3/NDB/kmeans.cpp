#include"kmeans.h"
#include"calDistance.h"
#include<time.h>
#include<numeric>
/*
	kmean聚类方法
	参数bData: 原始数据
	参数nDBs: 生成的负数据库
	参数iteration: 迭代次数
	参数k: kmeans中的k参数
	参数colLen: 每个属性占用的二进制位数
	返回结果：聚类中心，聚类中心中包含中心点及聚类结果
*/
vector<Cluster> kmeans(vector<NDB> nDBs, int iteration, int k, vector<int> colLen)
{
	//数据行数
	int row_num = nDBs.size();                  
	
    /*
		初始化聚类中心
	*/
	vector<Cluster> clusters(k); //大小为k
	
	//随机数种子
	int seed = (int)time(NULL);
	
	/*
		随机生成聚类中心
	*/
	for (int i = 0; i < k; i++)
	{
		/*
			产生随机数
		*/
		srand(seed);
		int randInt = rand() % row_num;

		double *nDBvalue = NDBvalue(nDBs[randInt],colLen);
		
		for (int j = 0; j < colLen.size(); j++) {
			clusters[i].centroid.push_back(nDBvalue[j]);
		}
		
		seed = rand();

		//!一定要释放
		delete[] nDBvalue;
	}


	/*多次迭代直至收敛*/
	for (int it = 0; it < iteration; it++)
	{
		cout << "第" << it + 1 << "次迭代";
		/*每一次重新计算样本点所属类别之前，清空原来样本点信息*/
		for (int i = 0; i < k; i++)
		{
			clusters[i].samples.clear();
		}
		/*求出每个样本点距应该属于哪一个聚类*/
		for (int j = 0; j < row_num; j++)
		{
			/*都初始化属于第0个聚类*/
			int c = 0;
			double min_distance = EuclidDis_NDB(nDBs[j], clusters[c].centroid, colLen);
			for (int i = 1; i < k; i++)
			{

				double distance = EuclidDis_NDB(nDBs[j], clusters[i].centroid, colLen);
				/*cout<<distance<<" ";*/
				if (distance < min_distance)
				{
					min_distance = distance;
					c = i;
				}

			}
			/*cout<<endl;*/
			cout << "第" << j << "个" << "样本聚类完成" << endl;
			clusters[c].samples.push_back(j);
		}

		/*更新聚类中心*/
		//count数组用于更新聚类中心
		
		double** count = new double*[k];
		
		for (int i = 0; i < k; ++i) {
			count[i] = new double[colLen.size()];
			
			//初始化为0
			for (int j = 0; j < colLen.size(); j++) {
				count[i][j] = 0.0;
			}
		}
		
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < clusters[i].samples.size(); j++)
			{
				int sample = clusters[i].samples[j];
				double *c = NDBvalue(nDBs[sample],colLen);
				
				for (int k = 0; k < colLen.size(); k++) {
					count[i][k] = count[i][k] + c[k];
				}
			}

			for (int j = 0; j < colLen.size(); j++) {
				clusters[i].centroid[j] = count[i][j] / clusters[i].samples.size();
			}
		}

		cout << "ok" << endl;
	}

	return clusters;
}

