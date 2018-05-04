#include <vector>
#include <GL/glut.h>
using namespace std;

class node{
public:
	float x, y;
	string label;
	GLfloat color[3];
	node(){
		x=0;
		y=0;
		label="";
	}
	// node(float xC,float yC,string labelC){
	// 	x=xC;
	// 	y=yC;
	// 	label=labelC;
	// 	//color=colorv;
	// }
	node(float xC,float yC,string labelC,GLfloat colorv[3]){
		x=xC;
		y=yC;
		label=labelC;
		color[0]=colorv[0];
		color[1]=colorv[1];
		color[2]=colorv[2];
	}
};
