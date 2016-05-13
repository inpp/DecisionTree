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

		for (int i = 0; i < Num_Att; i++) {
			tmp.att.resize(Num_Att, 0);
			fin >> str; // buying
			if (i==0&&fin.eof()) // ���� ����ִٸ� ����.
				break;
			fout << str << "\t";

			int equal = -1;
			for (int j = 0; j < AttSize[i]; j++) { // ������ �Ӽ��� ���� ��Ʈ���� ��ġ�ϸ� �ε��� �־��ֱ�
				if (str == AttString[i][j]) {
					equal = j;
					break;
				}
			}
			tmp.att[i] = equal;
		}
		if (fin.eof()) // ���� ����ִٸ� ����.
			break;
		// label�� ���� �ڷḦ ���� �� �ο�.
		vector<int> bagging_value;
		bagging_value.resize(AttSize[Num_Att], 0);
		for (int i = 0; i < bagging_num; i++) {
			bagging_value[Classify(tmp, Tree[i])]++;
		}
		int mode_value = 0;
		int max = bagging_value[0];
		for (int i = 1; i < AttSize[Num_Att]; i++) {
			if (bagging_value[i] > max) {
				max = bagging_value[i];
				mode_value = i;
			}
		}
		
		tmp.label = mode_value;
		fout << AttString[Num_Att][tmp.label] << "\n";

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