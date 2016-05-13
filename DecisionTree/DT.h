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