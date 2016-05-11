#include "DT.h"

bool FileRead(EXAMPLE &exam);
void DTL(Node &Parent, EXAMPLE Exam, vector<int> Att_Num, Node def);
bool TEST_IN(EXAMPLE &TestSet, const Node &Root);

int main(int agrc, char **argv) {
	EXAMPLE Exam_Set;
	EXAMPLE Test_Set;
	
	if (!FileRead(Exam_Set)) {
		cout << "입력받은 값이 존재하지 않습니다. 함수를 종료합니다" << endl;
		return 0;
	}


	Node Root;
	Node def;
	
	def.IsEnd = 0;

	vector<int> Att_Num;
	for (int i = 0; i < Num_Att; i++)
		Att_Num.push_back(i);

	cout << "트리 생성 시작\n";
	DTL(Root, Exam_Set, Att_Num, def);
	cout << "트리 생성 완료\n";
	
	cout << "TEST Data 분류 시작\n";
	if (!TEST_IN(Test_Set, Root))
		cout << "TEST Data 입력 실패\n";
	cout << "분류 완료, 시스템을 종료합니다.\n";

	system("pause");
	return 0;
}