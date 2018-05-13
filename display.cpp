// #include "Text/text.cpp"
#include "ext.cpp"
#include <SOIL/SOIL.h>

void display()
{
	//To display title page
	if(displayName)
	{
		glColor3f(1,1,1);
		GLuint texture = SOIL_load_OGL_texture("home.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB );
		glGenTextures(1, &texture);
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_POLYGON);
			glTexCoord2i(1,1); glVertex2i(1314, 744);
    		glTexCoord2i(1,0); glVertex2i(1314, 0);
    		glTexCoord2i(0,0); glVertex2i(0, 0);
    		glTexCoord2i(0,1); glVertex2i(0, 744);
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
		glDeleteTextures(1,&texture);
		cout<<SOIL_last_result()<<endl;
		glFlush();
		return;
	}
	//To display instruction screen
	if(displayInstruc){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,1,1);
		GLuint texture = SOIL_load_OGL_texture("instructions.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
		glGenTextures(1, &texture);
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_POLYGON);
			glTexCoord2i(1,1); glVertex2i(1314, 744);
    		glTexCoord2i(1,0); glVertex2i(1314, 0);
    		glTexCoord2i(0,0); glVertex2i(0, 0);
    		glTexCoord2i(0,1); glVertex2i(0, 744);
		glEnd();
		
		cout<<SOIL_last_result()<<endl;
		// SOIL_free_image_data(texture);
		glDisable(GL_TEXTURE_2D);
		glDeleteTextures(1,&texture);
		glFlush();
		return;
	}

	glDisable(GL_TEXTURE_2D);
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
	//Add transition button
	glColor3f(0.6999,0.6999,0.68);
	glBegin(GL_POLYGON);
		glVertex2f(140,744-43);
		glVertex2f(140,744-8);
		glVertex2f(280,744-8);
		glVertex2f(280,744-43);
	glEnd();

	glColor3f(0,0,0);
	renderBitmapString(150,744 - 33,"Add Transition",GLUT_BITMAP_HELVETICA_18);
	//Test FSM button
	glColor3f(0.6999,0.6999,0.68);
	glBegin(GL_POLYGON);
		glVertex2f(290,744-8);
		glVertex2f(290,744-43);
		glVertex2f(390,744-43);
		glVertex2f(390,744-8);
	glEnd();

	glColor3f(0,0,0);
	renderBitmapString(300,744-33,"Test FSM",GLUT_BITMAP_HELVETICA_18);
	//Screenshot button
	glColor3f(0.6999,0.6999,0.68);
	glBegin(GL_POLYGON);
		glVertex2f(1190,744-8);
		glVertex2f(1190,744-43);
		glVertex2f(1310,744-43);
		glVertex2f(1310,744-8);
	glEnd();

	glColor3f(0,0,0);
	renderBitmapString(1205,744-33,"Screenshot",GLUT_BITMAP_HELVETICA_18);

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

		drawCircle(MOUSEx,MOUSEy,30,n.color);
		glColor3f(0,0,0);
		renderBitmapString(MOUSEx-6,MOUSEy-2,n.label,GLUT_BITMAP_HELVETICA_18);
		//Four points for nodes
		if(transition_input!=0){
			GLfloat color[] = {0.1,0.1,0.1};
			drawCircle(n.x-30,n.y,5,color);
			drawCircle(n.x+30,n.y,5,color);
			drawCircle(n.x,n.y-30,5,color);
			drawCircle(n.x,n.y+30,5,color);
		}

		//Start state line
		if(!startState.compare(n.label)){
			// glPointSize(5);
			glColor3f(0,0,0);
			glLineWidth(3);
			glBegin(GL_LINES);
				glVertex2f(n.x-30,n.y);
				glVertex2f(n.x-70,n.y);
			glEnd();
			glBegin(GL_TRIANGLES);
				glVertex2f(n.x-29,n.y);
				glVertex2f(n.x-42,n.y+12);
				glVertex2f(n.x-42,n.y-12);
			glEnd();
		}
	}
	// cout<<"finalstate: ";
	//To draw final states
	for(int i=0;i<final_state_index.size();i++){
		draw_hollow_circle(nodes[final_state_index[i]].x,nodes[final_state_index[i]].y,0,20);
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
		//Draw transition lines
		glLineWidth(2);
		if(t.n1 != t.n2)
			spline(t.nx1,t.ny1,t.nx2,t.ny2,t.cx,t.cy);
		else
			self_loop(t.n1);
		t.cx = point[0];
		t.cy = point[1];
		string symbol = "";
		for(int i = 0;i < t.label.size();i++){
			symbol.append(t.label[i]);
			symbol.append(",");
			// cout<<"Actual"<<t.label[i];
		}
		symbol.pop_back();
		// cout<<endl<<symbol<<endl; @changed
		glColor3f(0, 0, 0);
		renderBitmapString(t.cx+2,t.cy+14,symbol,GLUT_BITMAP_HELVETICA_18);
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
