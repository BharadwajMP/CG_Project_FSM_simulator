#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;
void drawCircle(GLsizei MOUSEx,GLsizei MOUSEy,GLfloat radius,GLfloat* color){
	GLUquadricObj *sphere;

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glTranslatef(MOUSEx, MOUSEy, 0);
	//GLfloat color[]={90.0/255.0, 142.0/255, 244.0/255.0};
	//glColor3f(90.0/255.0, 142.0/255, 244.0/255.0);
	glColor3fv(color);
	// cout<<"In circle color: "<<color[0]<<" "<<color[1]<<" "<<color[2]<<endl;
		gluSphere(sphere, radius, 400, 400);
	glTranslatef(-MOUSEx, -MOUSEy, 0);
}
