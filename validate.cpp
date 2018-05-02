#include "display.cpp"
// #include "ext.cpp"

//Returns the next node to be traversed, if not found returns a null node
node search(vector<transition> transitions,node current,string label){
	vector<string> t_label;
	vector <transition> :: iterator j;
	for (j = transitions.begin(); j != transitions.end(); ++j){
		transition t=*j;
		t_label=t.label;
		vector<string>::iterator i;
		for(i=t_label.begin();i!=t_label.end();++i){
			if(*i==label && t.n1.label==current.label){
				 return t.n2;
			}
		}

	}
	node n;
	n.label="NULL";
	return n;
}


void validate(vector<node> nodes,vector<transition> transitions,string testString){
	vector <transition> :: iterator j;
		for (j = transitions.begin(); j != transitions.end(); ++j){
			transition t=*j;
			cout<<"Transition from node "<<t.n1.label<<" to node "<<t.n2.label<<endl;
		}
	string finalState="s1"; //Change this to make it dynamic
	int index=0;
	node current;
	vector<node> :: iterator i;
	//Replace the below block which assigns the start state
	for (i = nodes.begin(); i != nodes.end(); ++i){
			node t=*i;
			if(t.label=="s0"){
				current=t;
				break;
			}
	}
	while(index<testString.length()){
		// current.color[0]=0.5;
		// current.color[1]=0.5;
		// current.color[2]=0.5;
		stringstream ss;
		string target;
		ss << testString.at(index);
		ss >> target;
		node next=search(transitions,current,target);
		if(next.label!="NULL"){
			cout<<"Move to state "<<next.label<<endl;  //90.0/255.0, 142.0/255, 244.0/255.0
			next.color[0]=255.0/255.0;
			next.color[1]=255.0/255.0;
			next.color[2]=255.0/255.0;
			current=next;
			display();
			cout<<"After display"<<endl;
			// cout<<"Color : "<<nodes[z].color[0]<<nodes[z].color[1]<<nodes[z].color[2]<<endl;
			int i=0;
			for(i=0;i<99999999;i++);
		}
		else
			break;
		index++;
	}
	if(current.label==finalState)
		cout<<"String valid"<<endl;
	else
		cout<<"String invalid"<<endl;

}
