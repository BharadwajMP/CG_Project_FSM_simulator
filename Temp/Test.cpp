#include<iostream>
#include <sstream>
#include "node.cpp"
#include<string>
#include<vector>
vector<string> t_label;
vector<node> nodes;
vector<transition> transitions;

// This function returns the label of the next node if there is a transition from the current state via the label
string search(string current,string label){
	vector <transition> :: iterator j;
	for (j = transitions.begin(); j != transitions.end(); ++j){
		transition t=*j;
		t_label=t.label;
		vector<string>::iterator i;
		for(i=t_label.begin();i!=t_label.end();++i){
			if(*i==label && t.n1.label==current){
				 return t.n2.label;
			}
		}
		
	}
	return "NULL";
}
int main(){
	//FSM to accept strings starting with even # of a's followed by even # of b's
	node* s0=new node(0,0,string("s0"));
	node* s1=new node(0,0,string("s1"));
	node* s2=new node(0,0,string("s2"));
	node* s3=new node(0,0,string("s3"));
	node* s4=new node(0,0,string("s4"));
	node* d=new node(0,0,string("d"));
		nodes.push_back(*s0);
		nodes.push_back(*s1);
		nodes.push_back(*s2);
		nodes.push_back(*s3);
		nodes.push_back(*s4);
		nodes.push_back(*d);
	t_label.push_back(string("a"));
	transition* t1=new transition(*s0,*s1,t_label);
	t_label.pop_back();		t_label.push_back(string("b"));
	transition* t2=new transition(*s0,*d,t_label);
	t_label.pop_back();		t_label.push_back(string("a"));
	transition* t3=new transition(*s1,*s2,t_label);
	t_label.pop_back();		t_label.push_back(string("b"));
	transition* t4=new transition(*s1,*d,t_label);
	t_label.pop_back();		t_label.push_back(string("a"));
	transition* t5=new transition(*s2,*s1,t_label);
	t_label.pop_back();		t_label.push_back(string("b"));
	transition* t6=new transition(*s2,*s3,t_label);
	t_label.pop_back();		t_label.push_back(string("a"));
	transition* t7=new transition(*s3,*d,t_label);
	t_label.pop_back();		t_label.push_back(string("b"));
	transition* t8=new transition(*s3,*s4,t_label);
	t_label.pop_back();		t_label.push_back(string("b"));
	transition* t9=new transition(*s4,*s3,t_label);
	t_label.pop_back();		t_label.push_back(string("a"));
	transition* t10=new transition(*s4,*d,t_label);
		transitions.push_back(*t1);
		transitions.push_back(*t2);
		transitions.push_back(*t3);
		transitions.push_back(*t4);
		transitions.push_back(*t5);
		transitions.push_back(*t6);
		transitions.push_back(*t7);
		transitions.push_back(*t8);
		transitions.push_back(*t9);
		transitions.push_back(*t10);
	string testStr;
	string finalState="s4";
	cout<<"Enter the string to test: ";
	cin>>testStr;
	int index=0;
	string current="s0";
	while(index<testStr.length()){
		stringstream ss;
		string target;
		ss << testStr.at(index);
		ss >> target;
		string next=search(current,target);
		if(next!="NULL"){
			cout<<"Move to state "<<next<<endl; 
			current=next;
		}
		else
			break;
		index++;
	}
	if(current==finalState)
		cout<<"String valid"<<endl;
	else
		cout<<"String invalid"<<endl;
	

}
