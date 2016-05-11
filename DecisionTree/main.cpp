#include "DT.h"

bool FileRead(EXAMPLE &exam);
void DTL(Node &Parent, EXAMPLE Exam, vector<int> Att_Num, Node def);
bool TEST_IN(EXAMPLE &TestSet, const Node &Root);

int main(int agrc, char **argv) {
	EXAMPLE Exam_Set;
	EXAMPLE Test_Set;
	
	if (!FileRead(Exam_Set)) {
		cout << "�Է¹��� ���� �������� �ʽ��ϴ�. �Լ��� �����մϴ�" << endl;
		return 0;
	}


	Node Root;
	Node def;
	
	def.IsEnd = 0;

	vector<int> Att_Num;
	for (int i = 0; i < Num_Att; i++)
		Att_Num.push_back(i);

	cout << "Ʈ�� ���� ����\n";
	DTL(Root, Exam_Set, Att_Num, def);
	cout << "Ʈ�� ���� �Ϸ�\n";
	
	cout << "TEST Data �з� ����\n";
	if (!TEST_IN(Test_Set, Root))
		cout << "TEST Data �Է� ����\n";
	cout << "�з� �Ϸ�, �ý����� �����մϴ�.\n";

	system("pause");
	return 0;
}