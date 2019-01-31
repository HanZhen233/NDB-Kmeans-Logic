#include<iostream>
#include"infile.h"

int main() {
	readData();
	for (int  i = 0; i < dData.size(); i++)
	{
		for (int  j = 0; j < dData[i].size(); j++)
		{
			cout << dData[i][j] << " ";
		}
		cout << endl;
	}
}