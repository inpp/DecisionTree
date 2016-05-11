#include "DT.h"
#include <string>
#include <fstream>

vector<int> AttSize = { 4, 4, 4, 3, 3, 3 };

bool FileRead(EXAMPLE &exam) {
	string str;
	ifstream fin;

	fin.open("dt_train1.txt");
	if (fin.is_open() == false) { // 오픈이 안 되는 경우 에러메시지 발생.
		cout << "dt_train file open error." << endl;
		return false;
	}
	getline(fin, str);
	
	/**********************************************************
	*int age; // <=30 == 0 , 31...40 == 1, >40 == 2
	*int income; // low == 0, medium == 1, high == 2
	*int student; // no == 0, yes == 1
	*int credit_rating; // fair == 0, excellent == 1;
	************************************************************/

	while (!fin.eof()) {
		Entity tmp;

		/******************************* 대형 인풋 전 테스트예제
		fin >> str; // age
		if(fin.eof()) // 만약 비어있다면 종료.
			break;
		if (str[0] == '<')
			tmp.age = 0;
		else if (str[0] == '3')
			tmp.age = 1;
		else
			tmp.age = 2;

		fin >> str; //income
		if (str[0] == 'l')
			tmp.income = 0;
		else if (str[0] == 'm')
			tmp.income = 1;
		else
			tmp.income = 2;

		fin >> str; //student
		if (str[0] == 'n')
			tmp.student = 0;
		else
			tmp.student = 1;

		fin >> str; //credit_rating
		if (str[0] == 'f')
			tmp.credit = 0;
		else
			tmp.credit = 1;

		fin >> str; //buy
		if (str[0] == 'n')
			tmp.buy = 0;
		else
			tmp.buy = 1;
			****************************************/


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