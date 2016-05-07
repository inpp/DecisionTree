#include "DT.h"
#include <math.h>

int CHOOSE_ATTRIBUTE(EXAMPLE Exam, vector<int> Att_Num);
float IG(EXAMPLE Exam, int i, float ia);
float I(float P, float N);
float SplitInfo(EXAMPLE Exam, int Att_Num);

//DTL 함수 구현
void DTL(Node &Parent, EXAMPLE Exam, vector<int> Att_Num, Node def){
	Node New_Node;
	/***********************************************************************************************/
	// 남아있는 Example이 없다면 default값 반환
	if (Exam.size() == 0) { 
		Parent = def;
		return;
	}

	/***********************************************************************************************/
	// Example이 모두 같은 Classification이라면 그 값 반환
	bool check = true;
	int classification = -1;
	for (int i = 0; i < Exam.size(); i++) { 
		if (classification == -1)
			classification = Exam[i].buy;
		else if (classification != Exam[i].buy) {
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
	// Att가 비어있다면 최빈값 반환
	if (Att_Num.size() == 0) {
		int P = 0;
		int N = 0;
		for (int i = 0; i < Exam.size(); i++) {
			if (Exam[i].buy == 0)
				N++;
			else
				P++;
		}
		if (P > N)
			New_Node.IsEnd = 1;
		else
			New_Node.IsEnd = 0;


		Parent = New_Node; // 최빈값을 반환
		return;
	}
	/***********************************************************************************************/
	
	/***********************************************************************************************/
	//그 외의 상황에서는 best인 ATT를 선택하고, ATT의 value별로 다시 DTL 실행
	int best = CHOOSE_ATTRIBUTE(Exam, Att_Num);

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

int CHOOSE_ATTRIBUTE(EXAMPLE Exam, vector<int> Att_Num) {
	float max = -987654321;
	int best = -1;

	float P = 0;
	float N = 0;

	for (int i = 0; i < Exam.size(); i++) {
		if (Exam[i].buy == 0)
			N++;
		else
			P++;
	}
	float ia = I(P, N);

	for (int i = 0; i < Att_Num.size(); i++) {

		
		float Estimate_Att= IG(Exam, Att_Num[i], ia); // ID3 Information gain 
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
float I(float P, float N) {

	if (P == 0 || N == 0)
		return 0;
	
	return - P / (P + N)	* log(P / (P + N)) / log(2) - N / (P + N) * log(N / (P + N)) / log(2);
}

float IG(EXAMPLE Exam, int Att, float ia) {
	float remainder = 0;
	float tmp = 0;
	vector<float> NumP;
	vector<float> NumN;
	float P = 0;
	float N = 0;

	NumP.resize(AttSize[Att], 0);
	NumN.resize(AttSize[Att], 0);

	for (int j = 0; j < Exam.size(); j++) {
		if (Exam[j].buy == 1) {
			P++;
			NumP[ Exam[j].getAtt(Att) ]++;
		}
		else {
			N++;
			NumN[Exam[j].getAtt(Att)]++;
		}
	}

	for (int j = 0; j < AttSize[Att]; j++) {
		remainder += (NumP[j] + NumN[j]) / (P + N) * I(NumP[j], NumN[j]);
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