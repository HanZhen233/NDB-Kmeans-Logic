#include<iostream>
#include"infile.h"
#include"toBString.h"
# include"toNDB.h"

using namespace std;
int main() {
	srand((unsigned)time(NULL));
	readData();
	for (int  i = 0; i < dData.size(); i++)
	{
		for (int  j = 0; j < dData[i].size(); j++)
		{
			cout << dData[i][j] << " ";
		}
		cout << endl;
	}
	toBinaryString();
	for (int i = 0; i < colLen.size(); i++)
	{
		cout << colLen[i]<<" ";
	}
	cout << endl;
	cout << bData[0]<<endl;
	toNDB();
	/*for (int  j = 0; j <  nDBs[0].nData.size(); j++)
	{
		for (int i = 0; i < K0; i++)
		{
			cout << nDBs[0].nData[j][i] << "\t";
		}
		cout << endl;
	}
	*/
	cout << nDBs[0].nData[0][K0-1]<<endl;
	cout << nDBs[1].nData[0][K0 - 1] << endl;
}