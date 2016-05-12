#include "DT.h"
#include <fstream>
#include <string>

int Classify(Entity &Ent, const Node &Root);

bool TEST_IN(EXAMPLE &TestSet, const vector<Node> &Tree, string filename) {
	ifstream fin;
	ofstream fout;
	string str;

	fin.open(filename);
	fout.open(filename_result);

	getline(fin, str);
	fout << str << "\tcar_evaluation" << endl;
	while (!fin.eof()) {
		Entity tmp;

		/*
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
		*/
		tmp.att.resize(Num_Att, 0);
		fin >> str; // buying
		if (fin.eof()) // 만약 비어있다면 종료.
			break;
		if (str[0] == 'v')
			tmp.att[0] = 0;
		else if (str[0] == 'h')
			tmp.att[0] = 1;
		else if (str[0] == 'm')
			tmp.att[0] = 2;
		else
			tmp.att[0] = 3;
		fout << str << "\t";


		fin >> str; // maint
		if (str[0] == 'v')
			tmp.att[1] = 0;
		else if (str[0] == 'h')
			tmp.att[1] = 1;
		else if (str[0] == 'm')
			tmp.att[1] = 2;
		else
			tmp.att[1] = 3;
		fout << str << "\t";


		fin >> str; // doors
		if (str[0] == '2')
			tmp.att[2] = 0;
		else if (str[0] == '3')
			tmp.att[2] = 1;
		else if (str[0] == '4')
			tmp.att[2] = 2;
		else
			tmp.att[2] = 3;
		fout << str << "\t";


		fin >> str; // persons
		if (str[0] == '2')
			tmp.att[3] = 0;
		else if (str[0] == '4')
			tmp.att[3] = 1;
		else
			tmp.att[3] = 2;
		fout << str << "\t";


		fin >> str; // lug_boot
		if (str[0] == 's')
			tmp.att[4] = 0;
		else if (str[0] == 'm')
			tmp.att[4] = 1;
		else
			tmp.att[4] = 2;
		fout << str << "\t";


		fin >> str; // safety
		if (str[0] == 'l')
			tmp.att[5] = 0;
		else if (str[0] == 'm')
			tmp.att[5] = 1;
		else
			tmp.att[5] = 2;
		fout << str << "\t";


		// label는 위의 자료를 토대로 값 부여.
		vector<int> bagging_value;
		bagging_value.resize(4, 0);
		for (int i = 0; i < bagging_num; i++) {
			bagging_value[Classify(tmp, Tree[i])]++;
		}
		int mode_value = 0;
		int max = bagging_value[0];
		for (int i = 1; i < 4; i++) {
			if (bagging_value[i] > max) {
				max = bagging_value[i];
				mode_value = i;
			}
		}
		tmp.label = mode_value; // 수정 필요,
		if (tmp.label == 0)
			fout << "unacc" << "\n";
		else if(tmp.label==1)
			fout << "acc" << "\n";
		else if (tmp.label == 2)
			fout << "good" << "\n";
		else if (tmp.label == 3)
			fout << "vgood" << "\n";

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