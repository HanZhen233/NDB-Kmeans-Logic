#include"kmeans.h"
#include"calDistance.h"
#include<time.h>
#include<numeric>
/*
	kmean���෽��
	����bData: ԭʼ����
	����nDBs: ���ɵĸ����ݿ�
	����iteration: ��������
	����k: kmeans�е�k����
	����colLen: ÿ������ռ�õĶ�����λ��
	���ؽ�����������ģ����������а������ĵ㼰������
*/
vector<Cluster> kmeans(vector<NDB> nDBs, int iteration, int k, vector<int> colLen)
{
	//��������
	int row_num = nDBs.size();                  
	
    /*
		��ʼ����������
	*/
	vector<Cluster> clusters(k); //��СΪk
	
	//���������
	int seed = (int)time(NULL);
	
	/*
		������ɾ�������
	*/
	for (int i = 0; i < k; i++)
	{
		/*
			���������
		*/
		srand(seed);
		int randInt = rand() % row_num;

		double *nDBvalue = NDBvalue(nDBs[randInt],colLen);
		
		for (int j = 0; j < colLen.size(); j++) {
			clusters[i].centroid.push_back(nDBvalue[j]);
		}
		
		seed = rand();

		//!һ��Ҫ�ͷ�
		delete[] nDBvalue;
	}


	/*��ε���ֱ������*/
	for (int it = 0; it < iteration; it++)
	{
		cout << "��" << it + 1 << "�ε���";
		/*ÿһ�����¼����������������֮ǰ�����ԭ����������Ϣ*/
		for (int i = 0; i < k; i++)
		{
			clusters[i].samples.clear();
		}
		/*���ÿ���������Ӧ��������һ������*/
		for (int j = 0; j < row_num; j++)
		{
			/*����ʼ�����ڵ�0������*/
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
			cout << "��" << j << "��" << "�����������" << endl;
			clusters[c].samples.push_back(j);
		}

		/*���¾�������*/
		//count�������ڸ��¾�������
		
		double** count = new double*[k];
		
		for (int i = 0; i < k; ++i) {
			count[i] = new double[colLen.size()];
			
			//��ʼ��Ϊ0
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

