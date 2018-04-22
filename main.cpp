#include<iostream>
#include<GL/glut.h>
#include "Text/text.cpp"
#include "circle.cpp"
#include "node.cpp"
#include<vector>
#include<string>
#include "input_box.cpp"
#include<math.h>
#include<sstream>
#include "Spline.cpp"
#include "mouse_to_window.cpp"

using namespace std;

vector<node> nodes;
vector<transition> transitions;
vector<string> tr_label;
node tr_nodes[2];
int size = 650;
int check = 0;
bool displayName = false;
bool createNode=false;
string message="Message Box";
string stateLabel = "";
string trLabel = "";
bool state_input = false;
bool tr_label_input = false;
bool change_control_point = false;
bool detect_drag = false;
int transition_input = 0;
float nx,ny;
void display()
{
	//To display title page
	if(displayName)
	{
		//Background
		glColor3f(0.184,0.31,0.31);
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(1314,0);
			glVertex2f(1314,744);
			glVertex2f(0,744);
		glEnd();

		//Strat button
		glColor3f(0,0,0);
		glBegin(GL_POLYGON);
			glVertex2f(565,355);
			glVertex2f(675,355);
			glVertex2f(675,405);
			glVertex2f(565,405);
		glEnd();
		//Project info
		renderStrokeFontString(1500,1600,"FSM Simulator",4,1,0,0,0.3);
		renderStrokeFontString(5400,1500,"Bharadwaj MP (1PE15CS037)",1,1,1,1,0.15);
		renderStrokeFontString(5400,1300,"Harsha MS (1PE15CS057)",1,1,1,1,0.15);
		renderStrokeFontString(3400,2180,"Start",1.2,0,1,0,0.17);

		glFlush();
		return;
	}

	//Menu bar
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(0,744);
		glVertex2f(0,744-50);
		glVertex2f(1314,744-50);
		glVertex2f(1314,744);
	glEnd();

	//Create node button
	glColor3f(0.6999,0.6999,0.68);
	glBegin(GL_POLYGON);
		glVertex2f(15,744-8);
		glVertex2f(15,744-43);
		glVertex2f(130,744-43);
		glVertex2f(130,744-8);
	glEnd();

	glColor3f(0,0,0);
	renderBitmapString(20,744-33,"Create Node",GLUT_BITMAP_HELVETICA_18);
	//transition=true;
	glColor3f(0.6999,0.6999,0.68);
	glBegin(GL_POLYGON);
		glVertex2f(140,744-43);
		glVertex2f(140,744-8);
		glVertex2f(280,744-8);
		glVertex2f(280,744-43);
	glEnd();
//	renderStrokeFontString(1650,6150,"Add Transition",3,0,0,0,0.1);
	glColor3f(0,0,0);
	renderBitmapString(150,744 - 33,"Add Transition",GLUT_BITMAP_HELVETICA_18);
	//test=true;
	glColor3f(0.6999,0.6999,0.68);
	glBegin(GL_POLYGON);
		glVertex2f(290,744-8);
		glVertex2f(290,744-43);
		glVertex2f(390,744-43);
		glVertex2f(390,744-8);
	glEnd();
//	renderStrokeFontString(3450,6150,"Test FSM",3,0,0,0,0.1);
	glColor3f(0,0,0);
	renderBitmapString(300,744-33,"Test FSM",GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(1350,0);
		glVertex2f(1350,50);
		glVertex2f(0,50);
	glEnd();
	glColor3f(0,0,0);
	renderBitmapString(200,25,message,GLUT_BITMAP_HELVETICA_18);

	//Display states
	vector <node> :: iterator i;
	for (i = nodes.begin(); i != nodes.end(); ++i){
		node n=*i;
		GLsizei MOUSEx=n.x;GLsizei MOUSEy=n.y;
		drawCircle(MOUSEx,MOUSEy,20);
		glColor3f(0,0,0);
		renderBitmapString(MOUSEx-6,MOUSEy-2,n.label,GLUT_BITMAP_HELVETICA_18);

	}
	//Display transition lines
	vector <transition> :: iterator j;
	for (j = transitions.begin(); j != transitions.end(); ++j){
		transition t=*j;
		glColor3f(0,0,0);
		//Draw transition lines
		glLineWidth(2);
		GLfloat x1,x2;
		if(t.n1.x>t.n2.x){
			x1=t.n1.x-20;
			x2=t.n2.x+20;
		}
		else{
			x1=t.n1.x+20;
			x2=t.n2.x-20;
		}

		spline(x1,t.n1.y,x2,t.n2.y,t.cx,t.cy);
		string symbol = "";
		for(int i = 0;i < t.label.size();i++){
			symbol.append(t.label[i]);
			symbol.append(",");
			// cout<<"Actual"<<t.label[i];
		}
		symbol.pop_back();
		cout<<endl<<symbol<<endl;
		glColor3f(0, 0, 0);
		renderBitmapString(t.cx,t.cy+10,symbol,GLUT_BITMAP_HELVETICA_18);
	}
	//Display input box to accept state name
	if(state_input){
		input_box();
		glColor3f(1,1,1);
		renderBitmapString(560,470,"Enter state name",GLUT_BITMAP_HELVETICA_18);
		glColor3f(0,0,0);
		renderBitmapString(540,440,stateLabel,GLUT_BITMAP_HELVETICA_18);
	}
	//Display input box to accept transition labels
	if(tr_label_input){
		input_box();
		glColor3f(1,1,1);
		renderBitmapString(548,470,"Enter transition label",GLUT_BITMAP_HELVETICA_18);
		glColor3f(0,0,0);
		renderBitmapString(540,440,trLabel,GLUT_BITMAP_HELVETICA_18);
	}
	glFlush();
}
//To detect drag
void mouseDrag(int x,int y){
	if(change_control_point && detect_drag){
		GLdouble win[3];
		convert(win, x, y);
		transitions[transitions.size()-1].cx=win[0];
		transitions[transitions.size()-1].cy=win[1];
		display();
		glColor3f(1, 0, 0);
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex2f(transitions[transitions.size()-1].cx, transitions[transitions.size()-1].cy);
		glEnd();
		glPointSize(1);
		glFlush();
	}
}

void mouseDetect(int button,int state,int x,int y)
{
	//To see if drag should be performed or not
	if(change_control_point == true && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		detect_drag = true;
	}else if(change_control_point == true && state == GLUT_UP && button == GLUT_LEFT_BUTTON){
		detect_drag = false;
	}

	if(displayName)//To check if start button is pressed
		if(x > 566 && x <675 && y > 341 && y < 386)
		{
			displayName = false;
		}

	if(transition_input!=0 && state == GLUT_DOWN){
		vector <node> :: iterator i;
		//Convert mouse to window coordinates
		GLdouble win[3];
		convert(win, x, y);
		x = win[0];
		y = win[1];
		for (i = nodes.begin(); i != nodes.end(); ++i){
			node n = *i;

			if(sqrt(pow(n.x-x,2)+pow(n.y-y,2))<=20){
				// cout<<"Inside"<<endl;
				//Add node into tr_nodes
				tr_nodes[2-transition_input]=n;
				transition_input--;
				cout<<transition_input<<endl;
				if(transition_input == 0){
					tr_label_input = true;
					message = "Enter transition symbols separated by comma for multiple symbols";
					display();
				}
				break;
			}
			// cout<<"Outside"<<endl;
		}
	}
	//Create node button clicked
	if(x>21 && x<168 && y>15 && y<52){
		message="Create Node Clicked";
		createNode=true;
		display();
	}
	if(createNode){
		message="Message Box";
		if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && !(x>21 && x<168 && y>15 && y<52)){
			// cout<<"In create node"<<endl;

			state_input  = true;
			stateLabel = "";
	    createNode=false;
			display();
			//Convert mouse coordinates to window coordinates
			GLdouble win[3];
			convert(win, x, y);
			nx = win[0];
			ny = win[1];
			return;
	    }
	}
	//Add transition Clicked
	if (x > 148 && x < 290 && y > 9 && y < 39) {
		message="Select the two stated to add transition";
		transition_input = 2;
		display();
	}
	// cout<<x<<" "<<y<<endl;
}

void key(unsigned char key,int x,int y){
	//To exit change transition onece enter is pressed
	if(change_control_point && key == 13){
		change_control_point=false;
		message="";
		display();
	}

	if(state_input == true){
		// cout<<"Key pressed : "<<key<<endl;
		// cout<<stateLabel<<endl;
		if(key == 13 && stateLabel.compare("")){
			// cout<<"Key pressed : Enter"<<endl;
			state_input = false;
			nodes.push_back(node(nx,ny,string(stateLabel)));
			display();
			return;
		}
		if(key == 8)
			{
				if(stateLabel.length() != 0)
					stateLabel.pop_back();
				display();
			}
		else{
			if(key != 13)//Only if enter key is not pressed
				stateLabel.append(string(&key,&key+1));
			display();
		}
	}

	if(tr_label_input){
		if(key == 13 && trLabel.compare("")){
			tr_label_input = false;
			stringstream s(trLabel);
			string l;
			while(getline(s, l, ',')){
				tr_label.push_back(l);
			}
			transitions.push_back(transition(tr_nodes[0],tr_nodes[1],tr_label));
			change_control_point = true;
			message = "Click and drag mouse to change transition curve.Press enter if done.";
			trLabel="";
			tr_label.clear();//Remove all the elements
			display();
			return;
		}
		if(key == 8)
			{
				if(trLabel.length() != 0)
					trLabel.pop_back();
				display();
			}
		else{
			if(key != 13)//Only if enter key is not pressed
				trLabel.append(string(&key,&key+1));
			display();
		}
	}
}


int main(int argc,char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowSize(size+400,size);
	glutInitWindowSize(1366,750);
	glutInitWindowPosition(0,0);
	glutCreateWindow("FSM Simulator");
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1,1,1,1);
	glutDisplayFunc(display);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0,1314,0,744,-700,700);
	glutMouseFunc(mouseDetect);
	glutMotionFunc(mouseDrag);
	glutKeyboardFunc(key);
	glutMainLoop();
}
