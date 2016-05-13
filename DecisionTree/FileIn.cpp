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
		for (int j = 0; j < AttSize[Num_Att]; j++) { // 각각의 속성에 대해 스트링이 일치하면 인덱스 넣어주고 아니라면 속성 하나 추가.
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
		/**********************************************************
		*int buying; // vhigh == 0 , high == 1, med == 2, low == 3
		*int maint; // vhigh == 0 , high == 1, med == 2, low == 3
		*int doors; // 2 == 0, 3 == 1, 4 == 2, 5more == 3
		*int persons; // 2 == 0, 4 == 1, more == 2
		*int lug_boot; // samll == 0, med == 1, big == 2
		*int safety; // low == 0, med == 1, high == 2
		************************************************************/

		/*tmp.att.resize(Num_Att, 0);

		fin >> str; // buying
		if(fin.eof()) // 만약 비어있다면 종료.
		break;
		if (str[0] == 'v')
			tmp.att[0] = 0;
		else if (str[0] == 'h')
			tmp.att[0] = 1;
		else if (str[0] == 'm')
			tmp.att[0] = 2;
		else
			tmp.att[0] = 3;

		fin >> str; // maint
		if (str[0] == 'v')
			tmp.att[1] = 0;
		else if (str[0] == 'h')
			tmp.att[1] = 1;
		else if (str[0] == 'm')
			tmp.att[1] = 2;
		else
			tmp.att[1] = 3;
			
		fin >> str; // doors
		if (str[0] == '2')
			tmp.att[2] = 0;
		else if (str[0] == '3')
			tmp.att[2] = 1;
		else if (str[0] == '4')
			tmp.att[2] = 2;
		else
			tmp.att[2] = 3;

		fin >> str; // persons
		if (str[0] == '2')
			tmp.att[3] = 0;
		else if (str[0] == '4')
			tmp.att[3] = 1;
		else 
			tmp.att[3] = 2;

		fin >> str; // lug_boot
		if (str[0] == 's')
			tmp.att[4] = 0;
		else if (str[0] == 'm')
			tmp.att[4] = 1;
		else
			tmp.att[4] = 2;
		
		fin >> str; // safety
		if (str[0] == 'l')
			tmp.att[5] = 0;
		else if (str[0] == 'm')
			tmp.att[5] = 1;
		else
			tmp.att[5] = 2;

		fin >> str; // label
		if (str[0] == 'u')
			tmp.label = 0;
		else if (str[0] == 'a')
			tmp.label = 1;
		else if (str[0] == 'g')
			tmp.label = 2;
		else
			tmp.label = 3;

		exam.push_back(tmp);
		*/
	}

	fin.close();

	if (exam.size() == 0)
		return false;
	return true;
}