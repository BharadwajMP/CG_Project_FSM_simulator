//#include "text.h"
using namespace std;
void renderStrokeFontString(float x,float y,string str,float width,float red,float green,float blue,float size)
{
	glColor3f(red,green,blue);
	glLineWidth(width);
	glPushMatrix();
	glScalef(size,size,1);
	glTranslatef(x,y,0);
	for(int i = 0;i<str.length();i++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,int(str[i]));
	glPopMatrix();
}

void renderBitmapString(float x,float y,string str,void* font)
{
	glRasterPos2f(x,y);

	for(int i = 0;i < str.length();i++)
		glutBitmapCharacter(font,int(str[i]));
}