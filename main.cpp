#include<iostream>
#include<GL/glut.h>
//#include "Text/text.cpp"
#include "circle.cpp"
#include "node.cpp"
#include "transition.cpp"
#include<vector>
#include<string>
#include "input_box.cpp"
#include<math.h>
#include<sstream>
#include "Spline.cpp"
#include "mouse_to_window.cpp"
#include "validate.cpp"
// #include "display.cpp"
#include "ext.cpp"
using namespace std;
int flag=-1;
vector<node> nodes;
vector<transition> transitions;
vector<string> tr_label;
int tr_nodes[2];
int size = 650;
int check = 0;
bool displayName = false;
bool createNode=false;
string message="Message Box";
string stateLabel = "";
string trLabel = "";
string testString="";
bool state_input = false;
bool tr_label_input = false;
bool test_input=false;
bool change_control_point = false;
bool detect_drag = false;
int transition_input = 0;
bool valid=false;
float nx,ny;


//To detect drag

void mouseDetect(int button,int state,int x,int y)
{
	//To see if drag should be performed or not
	if(change_control_point == true && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
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
	}else if(change_control_point == true && state == GLUT_UP && button == GLUT_LEFT_BUTTON){
		detect_drag = false;
	}

	if(displayName)//To check if start button is pressed
		if(x > 566 && x <675 && y > 341 && y < 386)
		{
			displayName = false;
		}

	if(transition_input!=0 && state == GLUT_DOWN){
		//Convert mouse to window coordinates
		GLdouble win[3];
		convert(win, x, y);
		x = win[0];
		y = win[1];
		for (int i=0; i < nodes.size();i++){

			if(sqrt(pow(nodes[i].x-x,2)+pow(nodes[i].y-y,2))<=20){
				// cout<<"Inside"<<endl;
				//Add node into tr_nodes
				tr_nodes[2-transition_input]=i;
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
	//cout<<x<<" "<<y<<endl;
	//Test FSM Clicked
	if(x > 303 && x < 404 && y > 11 && y < 42){
		//cout<<"Test FSM clicked"<<endl;
		test_input=true;
		display();

	}
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
			GLfloat color[]={90.0/255.0, 142.0/255, 244.0/255.0};
			nodes.push_back(node(nx,ny,string(stateLabel),color));
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

	if(test_input){
		// cout<<"Key pressed : "<<key<<endl;
		// cout<<stateLabel<<endl;
		if(key == 13 && testString.compare("")){
			// cout<<"Key pressed : Enter"<<endl;
			test_input = false;
			validate(nodes,transitions,testString);
			display();
			return;
		}
		if(key == 8)
			{
				if(testString.length() != 0)
					testString.pop_back();
				display();
			}
		else{
			if(key != 13)//Only if enter key is not pressed
				testString.append(string(&key,&key+1));
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
	//glEnable(GL_COLOR_MATERIAL);
	glClearColor(1,1,1,1);
	glutDisplayFunc(display);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0,1314,0,744,-700,700);
	glutMouseFunc(mouseDetect);
	// glutMotionFunc(mouseDrag);
	glutKeyboardFunc(key);
	glutMainLoop();

}
