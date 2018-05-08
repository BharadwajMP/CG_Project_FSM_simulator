// #include "Text/text.cpp"
#include "ext.cpp"
// void myMenu(int id){
// 	cout<<id<<endl;
// }
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
	//Menu
	// int menu_id=glutCreateMenu(myMenu);
	// glutAddMenuEntry("WOrking",1);
	// glutAttachMenu(GLUT_RIGHT_BUTTON);

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
	int z=-1;
	if(flag!=-1){//Change color of selected node
		// cout<<"While redraw"<<endl;
		nodes[flag].color[0]=0;
		nodes[flag].color[1]=255.0/255.0;
		nodes[flag].color[2]=255.0/255.0;
	}
	for (i = nodes.begin(); i != nodes.end(); ++i){
		node n=*i;
		z++;
		GLsizei MOUSEx=n.x;GLsizei MOUSEy=n.y;
		//GLfloat color[]={90.0/255.0, 142.0/255, 244.0/255.0};

			// cout<<"Color : "<<z<<" "<<n.color[0]<<n.color[1]<<n.color[2]<<endl;
		drawCircle(MOUSEx,MOUSEy,20,n.color);
		glColor3f(0,0,0);
		renderBitmapString(MOUSEx-6,MOUSEy-2,n.label,GLUT_BITMAP_HELVETICA_18);

	}

	if(flag!=-1){
		// nodes[flag].color[0]=90.0/255.0;//Reset color
		nodes[flag].color[0]=0;
		nodes[flag].color[1]=142.0/255;
		nodes[flag].color[2]=244.0/255.0;
	}
	//Display transition lines
	vector <transition> :: iterator j;
	for (j = transitions.begin(); j != transitions.end(); ++j){
		transition t=*j;
		// glColor3f(0,0,0);
		//Draw transition lines
		glLineWidth(2);
		GLfloat x1,x2;
		if(nodes[t.n1].x>nodes[t.n2].x){
			x1=nodes[t.n1].x-20;
			x2=nodes[t.n2].x+20;
		}
		else{
			x1=nodes[t.n1].x+20;
			x2=nodes[t.n2].x-20;
		}

		spline(x1,nodes[t.n1].y,x2,nodes[t.n2].y,t.cx,t.cy);
		string symbol = "";
		for(int i = 0;i < t.label.size();i++){
			symbol.append(t.label[i]);
			symbol.append(",");
			// cout<<"Actual"<<t.label[i];
		}
		symbol.pop_back();
		// cout<<endl<<symbol<<endl; @changed
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
	if(test_input){
		input_box();
		glColor3f(1,1,1);
		renderBitmapString(548,470,"Enter string to test",GLUT_BITMAP_HELVETICA_18);
		glColor3f(0,0,0);
		renderBitmapString(540,440,testString,GLUT_BITMAP_HELVETICA_18);
	}
	if(displayValidateStatus){
		input_box();
		glColor3f(1,1,1);
		renderBitmapString(548,470,"Validation Status",GLUT_BITMAP_HELVETICA_18);
		glColor3f(0,0,0);
		renderBitmapString(540,440,validateString,GLUT_BITMAP_HELVETICA_18);
		for(int i=0;i<999999;i++);
		
	}
	if(showNext){
		
		glColor3f(0.6999,0.6999,0.68);
		glBegin(GL_POLYGON);
			glVertex2f(1280,744-103);
			glVertex2f(1280,744-77);
			glVertex2f(1240,744-77);
			glVertex2f(1240,744-103);
		glEnd();
		glColor3f(0,0,0);
		renderBitmapString(1250,744-92,">>",GLUT_BITMAP_HELVETICA_18);
	}
	//renderBitmapString(740,760,"Input String: "+testString,GLUT_BITMAP_HELVETICA_18);
	renderBitmapString(840,640,instructions,GLUT_BITMAP_HELVETICA_18);
	glFlush();
}
