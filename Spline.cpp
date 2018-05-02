#include <GL/glut.h>
#include <math.h>

typedef struct wcPt3D
{
	GLfloat x, y, z;
}wcPt3D;

void bino(GLint n, GLint *C)
{
        GLint k, j;

        for(k=0; k<=n; k++)
        {
                C[k]=1;

                for(j=n; j>=k+1; j--)
                        C[k]*=j;

                for(j=n-k; j>=2; j--)
                        C[k]/=j;
        }
}

void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts,GLint *C)
{
        GLint k, n = nCtrlPts-1;
        GLfloat bezBlendFcn;
        bezPt->x = bezPt->y = bezPt->z = 0.0;

        for(k=0; k< nCtrlPts; k++)
        {
                bezBlendFcn = C[k] * pow(u, k) * pow( 1-u, n-k);
                bezPt->x += ctrlPts[k].x * bezBlendFcn;
                bezPt->y += ctrlPts[k].y * bezBlendFcn;
                bezPt->z += ctrlPts[k].z * bezBlendFcn;
        }
}

void spline(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat cx,GLfloat cy)
{
        wcPt3D ctrlPts[3] = {{x1,y1,0},{cx,cy,0},{x2,y2,0}};
        wcPt3D bezCurvePt;
        GLfloat u;
        GLint *C, k;
        C= new GLint[3];
        bino(2, C);
        glBegin(GL_LINE_STRIP);
        int nBezCurvePts = 50;
        int nCtrlPts = 3;

        glColor3f(0, 0, 0);
        for(k=0; k<=nBezCurvePts; k++)
        {
                u=GLfloat(k)/GLfloat(nBezCurvePts);
                computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
                glVertex2f(bezCurvePt.x, bezCurvePt.y);
        }
        glEnd();

        wcPt3D a;
        u=25.0/GLfloat(nBezCurvePts);
        computeBezPt(u, &a, nCtrlPts, ctrlPts, C);
        wcPt3D b;
        u=24.0/GLfloat(nBezCurvePts);
        computeBezPt(u, &b, nCtrlPts, ctrlPts, C);

        float m = (a.y-b.y)/(a.x-b.x);

				glColor3f(0, 0, 1);
        glPushMatrix();
        glTranslatef(a.x, a.y, 0);
				if(x1>x2){
					// cout<<"Rotated 180"<<endl;
					glRotatef(180, 0, 0, 1);
				}
        glRotatef(atan(m)*180/3.14, 0, 0, 1);
				// cout<<"m = "<<m<<" angle = "<<atan(m)*180/3.14<<endl;
				glTranslatef(-a.x , -a.y,0);
        glBegin(GL_TRIANGLES);
          //To calculate other points on the triangle
          glVertex2f(a.x, a.y);
          glVertex2f(a.x-14, a.y+10);
          glVertex2f(a.x-14, a.y-10);
        glEnd();
        glRotatef(-atan(m)*180/3.14, 0, 0, 1);
        glPopMatrix();
        delete []C;
}
