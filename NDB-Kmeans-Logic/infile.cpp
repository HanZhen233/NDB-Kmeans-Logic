#include"infile.h"
vector<vector<double>> dData;
void readData() {
	string s ,s1;
	fstream in;
	in.open(INPUTFILENAME,ios::in);
	//out.open("inputData/wine1.txt", ios::out);
	while (getline(in, s)) {
		//s1 = s.substr(2, n - 1);
		//out << s1<<endl;
		dData.push_back(splitData(s,","));
		//s1 = s;
	}
	in.close();
}

vector<double> splitData(string s,string f) {
	 vector<double> rowData;
	string d0;
	string::size_type pos1, pos2;
	double d1;
	pos1 = 0;
	pos2 = s.find(f);
	while (string::npos!=pos2)
	{
	    d0 = s.substr(pos1, pos2 - pos1);
		d1 = atof(d0.c_str());
		rowData.push_back(d1);
		pos1 = pos2 + f.size();
		pos2 = s.find(f, pos1);
	}
	 d0 = s.substr(pos1,s.size());
	d1 = atof(d0.c_str());
	rowData.push_back(d1);
	return rowData;
}