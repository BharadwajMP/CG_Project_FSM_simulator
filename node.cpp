#include <vector>

using namespace std;

class node{
public:
	float x, y;
	string label;
	node(){
		x=0;
		y=0;
		label="";
	}
	node(float xC,float yC,string labelC){
		x=xC;
		y=yC;
		label=labelC;
	}
};

class transition{
public:
	node n1, n2; //Two nodes for which transition is to be made
	vector<string> label;//Input for which transition happens

	transition(node x1,node y1,vector<string> labelC){
		n1=x1;
		n2=y1;
		label=labelC;
	}
};