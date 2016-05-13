#include "DT.h"
#include <math.h>

int CHOOSE_ATTRIBUTE(EXAMPLE Exam, vector<int> Att_Num, vector<float> Num_Label);
float IG(EXAMPLE Exam, int i, float ia, vector<float> Num_Label);
float I(vector<float> Num_Label);
float SplitInfo(EXAMPLE Exam, int Att_Num);
float Sub_I(float x, float max);



//DTL 함수 구현
void DTL(Node &Parent, EXAMPLE Exam, vector<int> Att_Num, Node def){
	vector<float> Num_Label;
	Node New_Node;
	Num_Label.resize(AttSize[Num_Att], 0);
	/***********************************************************************************************/
	/**************************** 남아있는 Example이 없다면 default값 반환 *************************/
	if (Exam.size() == 0) { 
		Parent = def;
		return;
	}

	/***********************************************************************************************/
	/********************** Example이 모두 같은 Classification이라면 그 값 반환 ********************/
	bool check = true;
	int classification = -1;
	for (int i = 0; i < Exam.size(); i++) { 
		if (classification == -1)
			classification = Exam[i].label;
		else if (classification != Exam[i].label) {
			check = false;
			break;
		}
	}
	if (check == true) {
		New_Node.IsEnd = classification;
		Parent = New_Node; // classification를 값으로 사용하면 됨.
		return;
	}

	/***********************************************************************************************/
	for (int i = 0; i < Exam.size(); i++) {
		Num_Label[Exam[i].label]++;
	}

	/******************************** Att가 비어있다면 최빈값 반환 *********************************/
	if (Att_Num.size() == 0) {
		float max = -987654321;
		int value = -1;
		for (int i = 0; i < AttSize[Num_Att]; i++) {
			if (max < Num_Label[i]) {
				value = i;
				max = Num_Label[i];
			}
		}

		New_Node.IsEnd = value;

		Parent = New_Node; // 최빈값을 반환
		return;
	}
	
	/***********************************************************************************************/
	/**************그 외의 상황에서는 best인 ATT를 선택하고, ATT의 value별로 다시 DTL 실행**********/
	int best = CHOOSE_ATTRIBUTE(Exam, Att_Num, Num_Label);

	Parent.best_att = best;
	Parent.Successor.resize(AttSize[best]);
	for (int i = 0; i < AttSize[best]; i++) {
		
		EXAMPLE New_Exam;
		for (int j = 0; j < Exam.size(); j++) {
			if (Exam[j].getAtt(best) == i)
				New_Exam.push_back(Exam[j]);
		}
		vector<int> New_Att;
		for (int j = 0; j < Att_Num.size(); j++) {
			if (Att_Num[j] != best)
				New_Att.push_back(Att_Num[j]);
		}
		DTL(Parent.Successor[i], New_Exam, New_Att, def);
	}
}

int CHOOSE_ATTRIBUTE(EXAMPLE Exam, vector<int> Att_Num, vector<float> Num_Label) {
	float max = -987654321;
	int best = -1;

	float ia = I(Num_Label);

	for (int i = 0; i < Att_Num.size(); i++) {
		float Estimate_Att= IG(Exam, Att_Num[i], ia, Num_Label); // ID3 Information gain 
		Estimate_Att /= SplitInfo(Exam, Att_Num[i]); // For using C4.5 (gain_ratio, SplintInfo), Use this code.
		if (Estimate_Att > max) {
			max = Estimate_Att;
			best = Att_Num[i];
		}
	}
	return best;
}

/******************************************************************************************************/
//ID3 Information gain 
float I(vector<float> Num_Label) {
	float rtn = 0;
	float sum = 0;

	for (int i = 0; i < Num_Label.size(); i++) {
		sum += Num_Label[i];
	}
	for (int i = 0; i < Num_Label.size(); i++) {
		rtn += Sub_I(Num_Label[i], sum);
	}

	return rtn;
}

float Sub_I(float x, float max) {
	if (x == 0)
		return 0;
	return -x / max * log(x / max) / log(2);
}

float IG(EXAMPLE Exam, int Att, float ia, vector<float> Num_Label) {
	float remainder = 0;
	float tmp = 0;

	vector<vector<float >> Num_Att_Label;
	vector<float > tmpfv;
	tmpfv.resize(AttSize[Num_Att], 0);
	Num_Att_Label.resize(AttSize[Att], tmpfv);

	for (int i = 0; i < Exam.size(); i++)
		Num_Att_Label[Exam[i].getAtt(Att)][Exam[i].label]++;

	float sum = 0;
	for (int i = 0; i < Num_Label.size(); i++) {
		sum += Num_Label[i];
	}

	for (int i = 0; i < AttSize[Att]; i++) {
		float Attsum = 0;
		for (int j = 0; j < AttSize[Num_Att]; j++) {
			Attsum += Num_Att_Label[i][j];
		}
		remainder += (Attsum) / (sum) * I(Num_Att_Label[i]);
	}

	return ia - remainder;
}
/******************************************************************************************************/


/******************************************************************************************************/
//C4.5 SplitInfo 
float SplitInfo(EXAMPLE Exam, int Att) {
	float rtn = 0;
	vector<float> NumD;
	float N = (float)Exam.size();

	NumD.resize(AttSize[Att], 0);

	for (int j = 0; j < Exam.size(); j++) {
		NumD[Exam[j].getAtt(Att)]++;
	}

	for (int j = 0; j < AttSize[Att]; j++) {
		if(NumD[j]!=0&&N!=0)
			rtn -= (NumD[j] / N) * log(NumD[j] / N) / log(2);
	}

	return rtn;
}

/******************************************************************************************************/