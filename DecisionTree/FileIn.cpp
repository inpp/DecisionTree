#include "DT.h"
#include <string>
#include <fstream>

bool FileRead(EXAMPLE &exam) {
	string str;
	ifstream fin;

	fin.open("dt_train.txt");
	if (fin.is_open() == false) { // 오픈이 안 되는 경우 에러메시지 발생.
		cout << "dt_train file open error." << endl;
		return false;
	}
	getline(fin, str);

	/*
	int age; // <=30 == 0 , 31...40 == 1, >40 == 2
	int income; // low == 0, medium == 1, high == 2
	int student; // no == 0, yes == 1
	int credit_rating; // fair == 0, excellent == 1;
	*/
	while (!fin.eof()) {
		Entity tmp;

		fin >> str; //age
		if (str[0]=='n'|| str[0] == 'y')
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

		exam.push_back(tmp);
	}

	fin.close();

	if (exam.size() == 0)
		return false;
	return true;
}