extern vector<node> nodes;

class transition{
public:
	int n1, n2; //Two nodes for which transition is to be made
	vector<string> label;//Input for which transition happens
	GLfloat cx,cy;//Control point
	GLfloat nx1,ny1,nx2,ny2;//Two points of nodes to connect
	transition(int x1,int y1,vector<string> labelC,GLfloat mx1,GLfloat my1,GLfloat mx2,GLfloat my2){
		n1=x1;
		n2=y1;
		label=labelC;
		cx=(nodes[x1].x+nodes[y1].x)/2;
		cy=(nodes[x1].y+nodes[y1].y)/2;
		nx1 = mx1;
		ny1 = my1;
		nx2 = mx2;
		ny2 = my2;
	}
};
