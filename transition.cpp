extern vector<node> nodes;

class transition{
public:
	int n1, n2; //Two nodes for which transition is to be made
	vector<string> label;//Input for which transition happens
	GLfloat cx,cy;
	transition(int x1,int y1,vector<string> labelC){
		n1=x1;
		n2=y1;
		label=labelC;
		cx=(nodes[x1].x+nodes[y1].x)/2;
		cy=(nodes[x1].y+nodes[y1].y)/2;
	}
};
