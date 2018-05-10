#include <GL/glut.h>
#include "Text/text.cpp"

void input_box(){
  //Dialog box
  glColor3f(0.47,0.47,0.47);
  glBegin(GL_POLYGON);
    glVertex2f(500,500);
    glVertex2f(500,380);
    glVertex2f(750,380);
    glVertex2f(750,500);
  glEnd();

  //Input box
  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
    glVertex2f(530,460);
    glVertex2f(720,460);
    glVertex2f(720,430);
    glVertex2f(530,430);
  glEnd();
  //Enter button
  glColor3f(0,0.409,0);
  glBegin(GL_POLYGON);
    glVertex2f(620,420);
    glVertex2f(720,420);
    glVertex2f(720,390);
    glVertex2f(620,390);
  glEnd();
  //Enter message
  glColor3f(1,1,1);
  renderBitmapString(628,400,"Press Enter",GLUT_BITMAP_8_BY_13);
}
