#pragma once

#include <iostream>
#include <vector>

using namespace std;


#define bagging_num 1
#define bagging_factor 0
#define filename_result "dt_result.txt"


extern vector<int> AttSize;
extern vector<vector<string >> AttString;
extern int Num_Att;
extern int DEF;
class Entity {
public:
	/*
	int age; // <=30 == 0 , 31...40 == 1, >40 == 2
	int income; // low == 0, medium == 1, high == 2
	int student; // no == 0, yes == 1
	int credit; // fair == 0, excellent == 1;
	int buy; // no == 0, yes == 1;

	int getAtt(int Att) {
		if (Att == 0)
			return age;
		if (Att == 1)
			return income;
		if (Att == 2)
			return student;
		return credit;
	}
	*/

	vector<int> att;
	int label;
	//vector<vector<string > > att_value;

	int getAtt(int Att) {
		return att[Att];
	}
};

class Node {
public:
	vector<Node> Successor;
	int IsEnd = -1;
	int best_att;
};

typedef vector<Entity> EXAMPLE;