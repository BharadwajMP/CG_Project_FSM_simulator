#include "display.cpp"

int searchNew(){
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

void decideNext(){
	int next=searchNew();
	if(next!=-1){
		//nodes[curPos].color[1]=1.0; 90.0/255.0, 142.0/255, 244.0/255.0
		int j;
		for(j=0;j<nodes.size();j++){
			if(nodes[j].label==current){
				break;
			}
		}
		nodes[j].color[0]=90.0/255.0;
		nodes[j].color[1]=142.0/255.0;
		nodes[j].color[2]=244/255.0;
		nodes[next].color[0]=1.0;
		nodes[next].color[1]=0.0;
		nodes[next].color[2]=0.0;
		current=nodes[next].label;
		instructions="Move to state "+nodes[next].label+" with input symbol "+testString[pos];
		cout<<instructions<<endl;
		pos++;
	}
	else if(next==-1 || pos==testString.length()){
		pos=testString.length();
		instructions="";
		doneParsing=true;
	}
	if(current==finalState&&pos==testString.length()){
		cout<<"Valid"<<endl;
		validateString="Input String Valid";
		instructions="";
		message="";
		displayValidateStatus=true;
		showNext=false;
	}
	else if(doneParsing){
		cout<<"Invalid!!"<<endl;
		validateString="Input String Invalid!!!";
		instructions="";
		message="";
		displayValidateStatus=true;
		doneParsing=false;
		showNext=false;
	}
	
	
	display();
}