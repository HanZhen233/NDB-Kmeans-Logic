#include"infile.h"
#include"tool.h"
vector<vector<double>> dData;
vector<string> labels;

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

/*
	读取带有label的文件，最后一列为label（支持0，1格式或者A,B格式），文件格式:
	floatN,floatN,floatN,1
	floatN,floatN,floatN,0
	floatN,floatN,floatN,0
	floatN,floatN,floatN,1
	floatN,floatN,floatN,0
	...,...,...,...,...
*/
void readDataWithLabel() {
	/*
		先将整个文件存储在一个tempFile变量中，
		一行对应一个string
	*/
	vector<vector<string> > tempFile;
	string s;
	string pattern = ",";
	
	fstream in;
	in.open(INPUTFILENAME, ios::in);

	while (getline(in, s)) {
		tempFile.push_back(split(s,pattern));
	}
	
	in.close();

	/*
		从string数组中提取数据和label
	*/
	getData(tempFile);
	labels = getLabel(tempFile);
}

/*
	获取数据部分
	目的：对dData进行赋值
*/
void getData(vector<vector<string> > tempFile) {
	int columnLen = tempFile[0].size();
	for (int i = 0; i < tempFile.size(); i++) {
		vector<double> rowData;
		for (int j = 0; j < columnLen-1; j++) {
			double tempDValue = atof(tempFile[i][j].c_str());
			rowData.push_back(tempDValue);
		}
		dData.push_back(rowData);
	}
}


/*
	返回结果
	目的：获取标签label部分
*/
vector<string> getLabel(vector<vector<string> > tempFile) {
	
	//返回的结果
	vector<string> labels;

	//记录数组的列长
	int columnLen = tempFile[0].size();

	//获取每一行的最后一个元素，push back入labels数组中
	for (int i = 0; i < tempFile.size(); i++) {
		string tempLabel = tempFile[i][columnLen - 1];
		labels.push_back(tempLabel);
	}

	return labels;
}