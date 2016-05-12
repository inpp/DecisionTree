#include "DT.h"
#include <random>
#include <ctime>
#include <functional>
#include <string>


bool FileRead(EXAMPLE &exam, string filename);
void DTL(Node &Parent, EXAMPLE Exam, vector<int> Att_Num, Node def);
bool TEST_IN(EXAMPLE &TestSet, const vector<Node> &Root, string filename);

int main(int agrc, char **argv) {
	EXAMPLE Exam_Set;
	EXAMPLE Test_Set;
	
	if (!FileRead(Exam_Set, argv[1])) {
		cout << "�Է¹��� ���� �������� �ʽ��ϴ�. �Լ��� �����մϴ�" << endl;
		return 0;
	}


	vector<Node> Root;
	Root.resize(bagging_num);
	Node def;
	
	def.IsEnd = 1;

	vector<int> Att_Num;
	for (int i = 0; i < Num_Att; i++)
		Att_Num.push_back(i);

	
	mt19937 engine((unsigned int)time(NULL));                    // MT19937 ���� ����
	uniform_int_distribution<int> distribution(1, 100);       // ���� ����
	auto generator = bind(distribution, engine);


	//int bagging_factor;
	cout << "Ʈ�� ���� ����\n";
	for (int i = 0; i < bagging_num; i++) {
		EXAMPLE Sub_Set;
		for (int j = 0; j < Exam_Set.size(); j++) {
			if (generator() >= 100 - bagging_factor)
				Sub_Set.push_back(Exam_Set[j]);
		}
		DTL(Root[i], Sub_Set, Att_Num, def);
	}
	cout << "Ʈ�� ���� �Ϸ�\n";
	
	cout << "TEST Data �з� ����\n";
	if (!TEST_IN(Test_Set, Root, argv[2]))
		cout << "TEST Data �Է� ����\n";
	cout << "�з� �Ϸ�, �ý����� �����մϴ�.\n";

	system("pause");
	return 0;
}