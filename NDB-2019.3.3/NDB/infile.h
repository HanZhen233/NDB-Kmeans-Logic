#pragma once
#include<iostream>
#include<fstream>
#include"global.h"
#include<string>
#include<vector>
#include <stdlib.h>
#include <time.h> 
using namespace std;
extern vector<vector<double>> dData;
extern vector<string> labels;
void readDataWithLabel();
void getData(vector<vector<string> > tempFile);
vector<string> getLabel(vector<vector<string> > tempFile);
void readData() ;
//splitº¯Êý
 vector<double> splitData(string s,string f);
