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
		cout << "입력받은 값이 존재하지 않습니다. 함수를 종료합니다" << endl;
		return 0;
	}


	vector<Node> Root;
	Root.resize(bagging_num);
	Node def;
	
	def.IsEnd = 1;

	vector<int> Att_Num;
	for (int i = 0; i < Num_Att; i++)
		Att_Num.push_back(i);

	
	mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
	uniform_int_distribution<int> distribution(1, 100);       // 생성 범위
	auto generator = bind(distribution, engine);


	//int bagging_factor;
	cout << "트리 생성 시작\n";
	for (int i = 0; i < bagging_num; i++) {
		EXAMPLE Sub_Set;
		for (int j = 0; j < Exam_Set.size(); j++) {
			if (generator() >= 100 - bagging_factor)
				Sub_Set.push_back(Exam_Set[j]);
		}
		DTL(Root[i], Sub_Set, Att_Num, def);
	}
	cout << "트리 생성 완료\n";
	
	cout << "TEST Data 분류 시작\n";
	if (!TEST_IN(Test_Set, Root, argv[2]))
		cout << "TEST Data 입력 실패\n";
	cout << "분류 완료, 시스템을 종료합니다.\n";

	system("pause");
	return 0;
}