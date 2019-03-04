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
	��ȡ����label���ļ������һ��Ϊlabel��֧��0��1��ʽ����A,B��ʽ�����ļ���ʽ:
	floatN,floatN,floatN,1
	floatN,floatN,floatN,0
	floatN,floatN,floatN,0
	floatN,floatN,floatN,1
	floatN,floatN,floatN,0
	...,...,...,...,...
*/
void readDataWithLabel() {
	/*
		�Ƚ������ļ��洢��һ��tempFile�����У�
		һ�ж�Ӧһ��string
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
		��string��������ȡ���ݺ�label
	*/
	getData(tempFile);
	labels = getLabel(tempFile);
}

/*
	��ȡ���ݲ���
	Ŀ�ģ���dData���и�ֵ
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
	���ؽ��
	Ŀ�ģ���ȡ��ǩlabel����
*/
vector<string> getLabel(vector<vector<string> > tempFile) {
	
	//���صĽ��
	vector<string> labels;

	//��¼������г�
	int columnLen = tempFile[0].size();

	//��ȡÿһ�е����һ��Ԫ�أ�push back��labels������
	for (int i = 0; i < tempFile.size(); i++) {
		string tempLabel = tempFile[i][columnLen - 1];
		labels.push_back(tempLabel);
	}

	return labels;
}