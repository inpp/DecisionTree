#include "DT.h"
#include <string>
#include <fstream>

vector<int> AttSize = { 4, 4, 4, 3, 3, 3 };

bool FileRead(EXAMPLE &exam, string filename) {
	string str;
	ifstream fin;

	fin.open(filename);
	if (fin.is_open() == false) { // 오픈이 안 되는 경우 에러메시지 발생.
		cout << "dt_train file open error." << endl;
		return false;
	}
	getline(fin, str);
	

	while (!fin.eof()) {
		Entity tmp;

		/**********************************************************
		*int buying; // vhigh == 0 , high == 1, med == 2, low == 3
		*int maint; // vhigh == 0 , high == 1, med == 2, low == 3
		*int doors; // 2 == 0, 3 == 1, 4 == 2, 5more == 3
		*int persons; // 2 == 0, 4 == 1, more == 2
		*int lug_boot; // samll == 0, med == 1, big == 2
		*int safety; // low == 0, med == 1, high == 2
		************************************************************/

		tmp.att.resize(Num_Att, 0);

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
	}

	fin.close();

	if (exam.size() == 0)
		return false;
	return true;
}