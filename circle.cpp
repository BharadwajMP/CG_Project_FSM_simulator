#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

//Hollow circle
void draw_hollow_circle(float xx, float yy, float zz, float r) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	// cout<<"Hollow: (x,y) = ("<<xx<<","<<yy<<")"<<endl;
	GLfloat twicePi = 2.0f * 3.14159;
	glLineWidth(1.6);
	glBegin(GL_LINE_LOOP);
	for(i = 0; i <= lineAmount;i++) {
		glVertex3f(
			xx + (r * cos(i * twicePi / lineAmount)),
			yy + (r * sin(i * twicePi / lineAmount)),
			0
		);
	}
	glEnd();
}

//Solid circle
void drawCircle(GLsizei xx,GLsizei yy,GLfloat r,GLfloat* color){
	// GLUquadricObj *sphere;
	//
	// sphere = gluNewQuadric();
	// gluQuadricDrawStyle(sphere, GLU_FILL);
	// glTranslatef(MOUSEx, MOUSEy, 0);
	// cout<<"Solid: (x,y) = ("<<xx<<","<<yy<<")"<<endl;
	glColor3fv(color);
	// 	gluSphere(sphere, radius, 400, 400);
	// glTranslatef(-MOUSEx, -MOUSEy, 0);
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * 3.14159;
	glLineWidth(1.6);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(xx, yy, 0);
	for(i = 0; i <= lineAmount;i++) {
		glVertex3f(
			xx + (r * cos(i * twicePi / lineAmount)),
			yy + (r * sin(i * twicePi / lineAmount)),
			0
		);
	}
	glEnd();
	glLineWidth(1.8);
	glColor3f(0, 0, 0);
	draw_hollow_circle(xx,yy,0,r);
}
