#include "display.cpp"
// #include "ext.cpp"

//Returns the next node to be traversed, if not found returns a null node
int search(string testString){
	vector<string> t_label;
	vector <transition> :: iterator j;
	for (j = transitions.begin(); j != transitions.end(); ++j){
		transition t=*j;
		t_label=t.label;
		
		for(int i=0; i<t_label.size();i++){
			if((t_label[i])[0]==testString[pos] && nodes[t.n1].label==current){
				 return t.n2;
			}
		}

	}
	return -1;
}
void validate(string testString){
	if(startState==""||finalState==""){
		cout<<"returning"<<endl;
		return;
	}
	node curr;
	vector<node> :: iterator i;

	//Replace the below block which assigns the start state
	for (i = nodes.begin(); i != nodes.end(); ++i){
			node t=*i;
			if(t.label==current){
				curr=t;
				break;
			}
	}
	int next=search(testString);
	if(next!=-1){
		nodes[next].color[0]=1.0;
		nodes[next].color[1]=0.0;
		nodes[next].color[2]=0.0;
		if(pos<testString.length()){
			pos++;
		}
		else
			pos=-1;
	}
	display();

}