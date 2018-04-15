#include <GL/glut.h>

void convert(GLdouble win[3],GLfloat x,GLfloat y){
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  GLdouble modelview[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

  GLdouble projection[16];
  glGetDoublev(GL_PROJECTION_MATRIX, projection);

  y = (float)viewport[3]-y;
  gluUnProject(x, y, 0, modelview, projection, viewport, &win[0], &win[1], &win[2]);
}
