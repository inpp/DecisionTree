#include "DT.h"
#include <fstream>
#include <string>

int Classify(Entity &Ent, const Node &Root);

bool TEST_IN(EXAMPLE &TestSet, const Node &Tree) {
	ifstream fin;
	ofstream fout;
	string str;

	fin.open("dt_test.txt");
	fout.open("dt_result.txt");

	getline(fin, str);
	fout << str << "\tClass:buys_computer" << endl;
	while (!fin.eof()) {
		Entity tmp;

		fin >> str; //age
		if (str[0] == 'e'|| str[0] == 'f')
			break;
		if (str[0] == '<')
			tmp.age = 0;
		else if (str[0] == '3')
			tmp.age = 1;
		else
			tmp.age = 2;
		fout << str << "\t";

		fin >> str; //income
		if (str[0] == 'l')
			tmp.income = 0;
		else if (str[0] == 'm')
			tmp.income = 1;
		else
			tmp.income = 2;
		fout << str << "\t";

		fin >> str; //student
		if (str[0] == 'n')
			tmp.student = 0;
		else
			tmp.student = 1;
		fout << str << "\t";

		fin >> str; //credit_rating
		if (str[0] == 'f')
			tmp.credit = 0;
		else
			tmp.credit = 1;
		fout << str << "\t";
		
		// buy는 위의 자료를 토대로 값 부여.
		tmp.buy = Classify(tmp, Tree);
		if (tmp.buy == 0)
			fout<< "no" << "\n";
		else
			fout << "yes" << "\n";

		TestSet.push_back(tmp);
	}
	fin.close();
	fout.close();

	if (TestSet.size() == 0)
		return false;
}

int Classify(Entity &Ent, const Node &Tree) {
	if (Tree.IsEnd != -1)
		return Tree.IsEnd;

	return Classify(Ent, Tree.Successor[Ent.getAtt(Tree.best_att)]);
}