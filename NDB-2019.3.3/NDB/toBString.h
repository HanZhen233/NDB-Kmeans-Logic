#pragma once
#include"global.h"
#include"infile.h"
#include<cmath>
#include<sstream>
extern vector<string> bData;//每条数据的二进制串
extern vector<int> colLen;//每列数据的二进制长度
void toBinaryString();
int findMaxBinaryLength(int v);
