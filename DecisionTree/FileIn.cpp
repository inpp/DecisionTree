#include "DT.h"
#include <string>
#include <fstream>

vector<int> AttSize;
vector<vector<string >> AttString;
int Num_Att = 0;
int DEF = 1;

bool FileRead(EXAMPLE &exam, string filename) {
	string str;
	ifstream fin;

	fin.open(filename);
	if (fin.is_open() == false) { // 오픈이 안 되는 경우 에러메시지 발생.
		cout << "dt_train file open error." << endl;
		return false;
	}
	getline(fin, str);

	for (int i = 0; i < (int)str.size(); i++) {
		if (str[i] == '\t')
			Num_Att++;	
	}
	AttSize.resize(Num_Att+1, 0);
	AttString.resize(Num_Att+1);

	while (!fin.eof()) {
		Entity tmp;
		bool check = 0;
		tmp.att.resize(Num_Att, 0);
		for (int i = 0; i < Num_Att; i++) {
			if (i == 0 && fin.eof()) // 만약 비어있다면 끝.
				break;
			fin >> str;
			int equal = -1;
			for (int j = 0; j < AttSize[i]; j++) { // 각각의 속성에 대해 스트링이 일치하면 인덱스 넣어주고 아니라면 속성 하나 추가.
				if (str == AttString[i][j]) {
					equal = j;
				}
				if (equal != -1)
					break;
			}
			if (equal == -1) {
				tmp.att[i] = AttSize[i];
				AttSize[i]++;
				AttString[i].push_back(str);
			}
			else {
				tmp.att[i] = equal;
			}
		}
		if (fin.eof()) // 만약 비어있다면 끝.
			break;
		fin >> str;
		int equal = -1;
		for (int j = 0; j < AttSize[Num_Att]; j++) { // 라벨에 대해서도 위와 같이 인덱싱을 해준다.
			if (str == AttString[Num_Att][j]) {
				equal = j;
			}
			if (equal != -1)
				break;
		}
		if (equal == -1) {
			if (str == "acc")
				DEF = AttSize[Num_Att];
			tmp.label = AttSize[Num_Att];
			AttSize[Num_Att]++;
			AttString[Num_Att].push_back(str);
		}
		else {
			tmp.label = equal;
		}

		exam.push_back(tmp);
	}

	fin.close();

	if (exam.size() == 0)
		return false;
	return true;
}