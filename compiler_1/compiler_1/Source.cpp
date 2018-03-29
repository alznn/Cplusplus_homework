#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Gate{
	string id;
	string type;
	Gate* input1;
	Gate* input2;
	int value;
	bool passby;
};
Gate gate[1000];
int sum=0;
int point = 0;
vector <Gate*> output;
vector <Gate*> input;
vector<Gate*> last;
//--------------------------------------------定義Gate------------------------------------------------
int AND(Gate* right , Gate* left){
	if( right->value == 1 && left->value == 1)
		return 1;
	else return 0;
}

int OR(Gate* right , Gate* left){
	if( right->value == 0 && left->value == 0)
		return 0;
	else return 1;
}

int NAND(Gate* right , Gate* left){
	if( AND(right , left) == 1)
		return 0;
	else return 1;
}

int NOR(Gate* right , Gate* left){
	if( OR(right , left) == 0)
		return 1;
	else return 0;
}

int XOR(Gate* right , Gate* left){
	if( right ->value == left -> value )
		return 0;
	else return 1;
}

int NXOR(Gate* right , Gate* left){
	if( right->value == left->value)
		return 1;
	else return 0;
}

int NOT(Gate* val){
	if( val->value == 0)
		return 1;
	else return 0;
}
/*--------------------------------------------定義Gate--------------------------------------------------*/

//new GATE
Gate* check_id(string id){
	for(int i = 0 ; i<sum+1 ; i++)
		if(gate[i].id == id)
			return &gate[i];	//存在直接指
	return NULL;
}

Gate* Setting(int pos , string id){
	gate[pos].id = id;
	gate[pos].type = "NULL"; 
	gate[pos].input1 = NULL;
	gate[pos].input2 = NULL;
	gate[pos].value = -1;
	return &gate[pos];
}
void get_token(string line)
{
	gate[sum].id = "NULL";
	gate[sum].type = "NULL";
	gate[sum].input1 = NULL;
	gate[sum].input2 = NULL;
	gate[sum].value = -1;

	//處理in / out
	if(	line.substr(0 , line.find("(") ) == "INPUT" || line.substr(0 , line.find("(") ) == "OUTPUT"){
		gate[sum].id =  line.substr(line.find("(")+1 , line.find(")" , line.find("("))-line.find("(")-1);
		gate[sum].type = line.substr(0 , line.find("(") );		//INTPUT  OUTPUT
		if(	gate[sum].type == "INPUT" )
			input.push_back(&gate[sum]);
		else if( gate[sum].type == "OUTPUT" )
			output.push_back(&gate[sum]);
	}
	//-----------------------------------------處理gate-------------------------------------------------------
	else{
		//------------------------------------判斷ID----------------------------------------------------------
		Gate *pointer = NULL;
		int current = 0;

		//Check id 重複
		pointer = check_id(line.substr(0 , line.find(" = ")));

		//重複id 
		if(pointer!= NULL){
			current = pointer - gate;
			cout<<"current: "<<current<<"\n";
			--sum;
			cout<<"sum:"<<sum<<"\n";
		}
		//id未重複
		else current = sum;

		//-------------------------------給定type------------------------------------------------------
		//BUFF & NOT
		gate[current].id = line.substr(0 , line.find(" = "));
		gate[current].type = line.substr(line.find(" = ")+3 , line.find("(" , line.find("="))-line.find(" = ")-3);

		cout<<"id: "<<gate[current].id<<"\n";
		cout<<"type: "<<gate[current].type<<"\n";


		if(line.substr(line.find(" = ")+3 , line.find("(" , line.find("="))-line.find(" = ")-3) == "BUFF" || line.substr(line.find(" = ")+3 , line.find("(" , line.find("="))-line.find(" = ")-3) == "NOT" ){
			//檢查input1
			pointer = check_id(line.substr(line.find("(")+1 , line.find(")" , line.find("("))-line.find("(")-1));
			if(pointer!= NULL){	//input1　exit
				gate[current].input1 = pointer;
			}
			else{
				point = sum;
				cout<<"point:　"<<point<<"\n";
				pointer = Setting(++point , (line.substr(line.find("(")+1 , line.find(")" , line.find("("))-line.find("(")-1)));
				gate[current].input1 = pointer;

			}
		}
		//其他剩餘的GATE
		else{
			/*----------------------------------------------------input1----------------------------------------------------------*/
			pointer = check_id(line.substr(line.find("(")+1 , line.find("," , line.find("("))-line.find("(")-1));
			if(pointer!= NULL)
				gate[current].input1 = pointer;
			else{
				point = sum;
				cout<<"point:　"<<point<<"\n";
				pointer = Setting(++point , line.substr(line.find("(")+1 , line.find("," , line.find("("))-line.find("(")-1));
				gate[current].input1 = pointer;
			}
			/*----------------------------------------------------input2----------------------------------------------------------*/


			pointer = check_id(line.substr(line.find(",")+2 , line.find(")" , line.find(","))-line.find(",")-2));
			if(pointer!= NULL)
				gate[current].input2 = pointer;
			else{
				point = sum;
				cout<<"point:　"<<point<<"\n";
				pointer = Setting(++point , line.substr(line.find(",")+2 , line.find(")" , line.find(","))-line.find(",")-2));
				gate[current].input2 = pointer;
			}
		}
	}
	if ( point > sum)  sum = point; 
	cout<<sum<<"\n";
	sum++;
}

void BackTrack (Gate* gate){
	int i =0;
	cout<<"id : "<<gate->id<<"\n";
	cout<<"type : "<<gate->type<<"\n";
	cout<<"value : "<<gate->value<<"\n";
	//	cout<<"input1: "<<gate->input1<<"\n";
	//system("pause");
	// BackTrack(gate->input1);
	if (gate->value != -1){
		//	cout<<gate->value;
		return ;
	}

	if(gate->input2 == NULL){
		BackTrack(gate->input1);
		if(gate -> type == "BUFF") {
			gate->value = gate->input1->value;
		} else if(gate -> type == "NOT") {
			gate->value = NOT(gate -> input1);
		}
	}
	else{
		if(gate->input1->value == -1)
			BackTrack(gate->input1);
		if (gate->input2->value == -1){
			BackTrack(gate ->input2);
		}

		if(gate->input1->value != -1 && gate->input2->value != -1){
			if(gate -> type =="AND")
				gate->value = AND( gate ->input1 ,gate ->input2 );
			else if(gate -> type =="NAND")
				gate->value = NAND(gate->input1 ,gate -> input2 );
			else if(gate -> type =="OR")
				gate->value = OR(gate->input1 ,gate -> input2 );
			else if(gate -> type =="NOR")
				gate->value = NOR(gate->input1 ,gate -> input2 );
			else if(gate -> type =="XOR")
				gate->value = XOR(gate->input1 ,gate -> input2 );
			else if(gate -> type =="NXOR")
				gate->value = NXOR(gate->input1 ,gate -> input2 );
		}

	}
}

void answer(){
	for(int i = 0 ; i< output.size(); )
	{
		cout<<output[i]->value;
		cout<<output[i]->id;
		while(output[i]->value == -1)
			BackTrack(output[i]);
		i++;
	}
}
int main(){
	string line;
	ifstream inputFile;
	//	string filename;
	inputFile.open("aaa.isc" , ifstream::in);
	while(!inputFile.eof()){
	getline(inputFile,line);
	cout<<"line:"<<line<<"\n";
	if(line.substr(0 , 1) =="#" || line.substr(0 , 1) ==" " || line.size() <3 )	;
	else	get_token( line );
	//	system("pause");
	}
	inputFile.close();
	cout<<"main sum : "<<sum<<"\n";

	//for(int i = 0 ; i < sum ; i++)
	//	cout<<gate[i].id <<"\n type: "<<gate[i].type<<"\n";
	/*	
	while(!cin.eof()){
		getline(cin,line);
		//		cout<<line<<"\n";
		if(line.substr(0 , 1) =="#" ||line.substr(0 , 1) == " " || line.size() <3) ;
		else	get_token( line );
		//system("pause");
	}*/
	//system("pause");
	for(int i = 0 ; i < input.size() ; i++)
		input[i]->value = 0;
	for(int i = 0 ; i < input.size() ; i++)
		cout<<input[i]->value;

	for(int i = 0 ; i < input.size() ; i++)
		input[i]->value = 1;
	answer();
	cout<<"result0 : ";
	for(int i = 0 ; i < output.size() ; i++)
		cout<<output[i]->value;

	cout<<endl;
	
	for(int i = 0 ; i < sum ; i++)
		gate[i].value = -1;
	for(int i = 0 ; i < input.size() ; i++)
		input[i]->value = 1;
	answer();
	cout<<"result1 : ";
	for(int i = 0 ; i < output.size() ; i++)
		cout<<output[i]->value;

	system("pause");
	return 0;

}