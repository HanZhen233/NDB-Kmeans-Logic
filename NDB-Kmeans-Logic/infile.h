#pragma once
#include<iostream>
# include<fstream>
#include"global.h"
#include<string>
#include<vector>
#include <stdlib.h>
#include <time.h> 
using namespace std;
extern vector<vector<double>> dData;
void readData() ;
//split����
 vector<double> splitData(string s,string f);
