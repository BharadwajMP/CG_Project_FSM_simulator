#include<GL/glut.h>
#include<math.h>
void drawCircle(GLsizei MOUSEx,GLsizei MOUSEy,GLfloat radius){
	GLUquadricObj *sphere;

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glTranslatef(MOUSEx, MOUSEy, 0);
	glColor3f(90.0/255.0, 142.0/255, 244.0/255.0);
		gluSphere(sphere, radius, 400, 400);
	glTranslatef(-MOUSEx, -MOUSEy, 0);
}
