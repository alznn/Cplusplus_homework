#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct K_map
{
	int w,x,y,z;
	int same;//判斷是否一致
	bool if_along ;//紀錄是否落單
};
K_map table[16];
K_map final_term[16];
int f_index = 0;
int record[16];

void Two_imp(int *term ,int size);
void pF_imp(K_map * result ,int size);
void Four_map(K_map * temp , int size);
void Eight_map(K_map * f_term , int size);
void Out_put(K_map * final_term , int f_index);

void Table(){
	for(int i=0 ; i<16 ; i++){    //初始化
		final_term[i].w = table[i].w = 0;
		final_term[i].x = table[i].x = 0;
		final_term[i].y = table[i].y = 0;
		final_term[i].z = table[i].z = 0;
	}
	for(int i=8 ; i<16 ; i++){	//w=1(8~15)
		table[i].w=1;
		if(i>=12)				//w=1 && x=1
			table[i].x=1;
	}
	for(int i=4 ; i<8 ; i++)	//x=1(4~6)
		table[i].x=1;
	for(int i=1 ; i<14 ; i+=4)	//z=1(1.5.9.13.19)
		table[i].z=1;
	for(int i=2 ; i<15 ; i+=4)	//y=1(2.6.10.14)
		table[i].y=1;
	for(int i=3 ; i<16 ; i+=4)	//z=1 && y=1(3.7.11.15)
		table[i].y=1,table[i].z=1;
}

void pick_term(int *map){
	Table();
	int * term = new int[16];//紀錄term
	int f_index = 0;
	int count = 0;
	for(int i = 0 ; i<16 ; i++){
		if(map[i] ==1 || map[i]==2){
			term[count]=0;
			term[count]=i;
			count++;
		}
	}
	cout<<endl<<"找term: ";
	for(int i = 0 ; i<count ; i++)
		cout<<term[i]<<" ";
	cout<<endl;
	Two_imp(term,count);
}

void Two_imp(int * term ,int size){    //第一次處理
	int psize=4*size;
	K_map * result1 = new K_map[ psize ];
	for(int i=0 ; i<size ; i++){    //初始化
		result1[i].w = 0;
		result1[i].x = 0;
		result1[i].y = 0;
		result1[i].z = 0;
	}
	for(int i=0 ; i<size ; i++){    //初始化
		table[term[i]].if_along=true;
	}

	int index = 0;
	for(int i = 0 ; i<size ; i++){
		for(int j = i+1 ; j<size ; j++){
			//	cout<<"i: "<<i<<"  "<<term[i]<<endl;
			table[term[i]].same=0;
			//	cout<<endl<<"確認w "<<endl
			//		<<term[i]<<" w  "<<table[term[i]].w<<"  "<<term[j]<<"w"<<table[term[j]].w<<endl;

			if(table[term[i]].w==table[term[j]].w)
				table[term[i]].same++;
			//	cout<<"確認x "<<endl
			//		<<term[i]<<"x  "<<table[term[i]].x<<"  "<<term[j]<<"x  "<<table[term[j]].x<<endl;
			if(table[term[i]].x==table[term[j]].x)
				table[term[i]].same++;
			//	cout<<"確認y "<<endl
			//		<<term[i]<<"y  "<<table[term[i]].y<<"  "<<term[j]<<"x  "<<table[term[j]].y<<endl;
			if(table[term[i]].y==table[term[j]].y)
				table[term[i]].same++;
			//	cout<<"確認z "<<endl
			//		<<term[i]<<"z  "<<table[term[i]].z<<"  "<<term[j]<<"y  "<<table[term[j]].z<<endl;
			if(table[term[i]].z==table[term[j]].z)
				table[term[i]].same++;

			//cout<<"現在的same : "<<table[term[i]].same<<endl;

			if(table[term[i]].same == 3){    //二成對
				table[term[i]].if_along = table[term[j]].if_along = false;//非落單

				if(table[term[i]].w==table[term[j]].w)
					result1[index].w=table[term[i]].w;
				else result1[index].w=-1;
				//cout<<endl<<index<<"  w  "<<result1[index].w;

				if(table[term[i]].x==table[term[j]].x)
					result1[index].x=table[term[i]].x;
				else result1[index].x=-1;
				//cout<<endl<<index<<"  x  "<<result1[index].x;

				if(table[term[i]].y==table[term[j]].y)
					result1[index].y=table[term[i]].y;
				else result1[index].y=-1;
				//cout<<endl<<index<<"  y  "<<result1[index].y;

				if(table[term[i]].z==table[term[j]].z)
					result1[index].z=table[term[i]].z;
				else result1[index].z=-1;
				//cout<<endl<<index<<"  z  "<<result1[index].z;
				index++;
			}
		}
	}
	for(int i = 0 ; i<size ; i++){
		if(table[term[i]].if_along == true){    //1term落單處理
			//			cout<<"T_imp 落單的"<<term[i];
			if(term[i] ==2)
				break;
			final_term[f_index].w =table[term[i]].w; 
			final_term[f_index].x =table[term[i]].x; 
			final_term[f_index].y =table[term[i]].y; 
			final_term[f_index].z =table[term[i]].z; 
			//			cout<<"f_index "<<f_index;
			f_index++;
		}
	}
	/*
	for(int i = 0 ; i <f_index ; i++){
	cout<<endl<<i<<endl;
	cout<<final_term[i].w;
	cout<<final_term[i].x;
	cout<<final_term[i].y;
	cout<<final_term[i].z;
	}
	cout<<"兩個包成的term"<<endl;;
	for(int i = 0 ; i <index ; i++){
		cout<<endl<<i<<endl;
		cout<<result1[i].w;
		cout<<result1[i].x;
		cout<<result1[i].y;
		cout<<result1[i].z;
	}
*/
	pF_imp(result1,index);

}

void pF_imp(K_map * result ,int size){    //第二次處理
	//cout<<"size: "<<size;
	int psize=100*size;
	K_map * temp = new K_map[ psize ];//convert temp
	int t_index = 0;//算被合併的總數

	for(int i = 0 ; i <psize ; i++)  //初始化
	{
		temp[i].if_along = true;
		temp[i].w=0;
		temp[i].x=0;
		temp[i].y=0;
		temp[i].z=0;
	}
	for(int i = 0 ; i<size-1 ; i++){  //兩個bit一樣就合併
		int count = 0;
		for(int j = 0 ; j<size ; j++){
			result[i].same=0;  
			//cout<<endl<<"確認 w "<<endl
			//<<"result"<<i<< " .w " << result[i].w <<"  "<<"result"<<j<<".w "<<result[j].w<<endl;
			if(result[i].w !=-1 && result[i].w==result[j].w)
				result[i].same++;
			//	cout<<endl<<"確認 x "<<endl
			//	<<"result"<<i<< " .x " << result[i].x <<"  "<<"result"<<j<<".x "<<result[j].x<<endl;
			if(result[i].x !=-1 && result[i].x==result[j].x)
				result[i].same++;
			//	cout<<endl<<"確認 y "<<endl
			//	<<"result"<<i<< " .y " << result[i].y <<"  "<<"result"<<j<<".y "<<result[j].y<<endl;
			if(result[i].y !=-1 && result[i].y==result[j].y)
				result[i].same++;
			//cout<<endl<<"確認 z "<<endl
			//<<"result"<<i<< " .z " << result[i].z <<"  "<<"result"<<j<<".z "<<result[j].z<<endl;
			if(result[i].z !=-1 && result[i].z==result[j].z)
				result[i].same++;
			//cout<<"SAME: "<<i<<"  "<<result[i].same<<endl;

			if(result[i].same==2){

				if(result[i].w !=-1 && result[i].w == result[j].w)
					temp[t_index].w=result[i].w;
				else temp[t_index].w=-1;
				//cout<<endl<<t_index<<"  w  "<<temp[t_index].w;

				if(result[i].x !=-1 && result[i].x == result[j].x)
					temp[t_index].x=result[i].x;
				else temp[t_index].x=-1;
				//cout<<endl<<t_index<<"  x  "<<temp[t_index].x;

				if(result[i].y !=-1 && result[i].y == result[j].y)
					temp[t_index].y=result[i].y;
				else temp[t_index].y=-1;
				//cout<<endl<<t_index<<"  y  "<<temp[t_index].y;

				if(result[i].z !=-1 && result[i].z == result[j].z)
					temp[t_index].z=result[i].z;
				else temp[t_index].z=-1;
				//cout<<endl<<t_index<<"  z  "<<temp[t_index].z;
				t_index++;
				//break;
				count++;
			}
		}
		if(count<3){
			final_term[f_index].w=result[i].w;
			final_term[f_index].x=result[i].x;
			final_term[f_index].y=result[i].y;
			final_term[f_index].z=result[i].z;
			f_index++;
		}
	}
	/*
	for(int i = 0 ; i <f_index ; i++){
	cout<<endl<<i<<endl;
	cout<<final_term[i].w;
	cout<<final_term[i].x;
	cout<<final_term[i].y;
	cout<<final_term[i].z;
	}
	cout<<endl<<"temp: ";
	/*for(int i = 0 ; i <t_index ; i++)
	{
	cout<<endl<<i<<"  ";
	cout<<temp[i].w;
	cout<<temp[i].x;
	cout<<temp[i].y;
	cout<<temp[i].z;
	}
	*/
	Four_map(temp , t_index);
}

void Four_map(K_map * temp , int size){
	int psize = size*4;
	K_map * four_term = new K_map[ psize ];
	int four_index= 0;
	for(int i = 0 ; i<size ; i++)
		temp[i].if_along = true;
	for(int i = 0 ; i<size; i++){    
		temp[i].same=0;	
		for(int j =i+1 ; j<size ; j++){
			if( temp[i].w == temp[j].w
				&& temp[i].x == temp[j].x
				&& temp[i].y == temp[j].y
				&& temp[i].z == temp[j].z)
				temp[i].same++;
			if(temp[i].same==3){
				for(int k=0 ; k<four_index ; k++)    //檢查four關係
					if(temp[i].w == four_term[k].w 
						&& temp[i].x == four_term[k].x 
						&& temp[i].y == four_term[k].y 
						&& temp[i].z == four_term[k].z){
							temp[i].if_along = false;
							break;
					}
					if(temp[i].if_along == true){   //化簡後結果
						four_term[four_index].w = temp[i].w;
						four_term[four_index].x = temp[i].x;
						four_term[four_index].y = temp[i].y;
						four_term[four_index].z = temp[i].z;
						four_index++;
					}
			}
		}
	}	
/*	cout<<"four_term: "<<endl;
	cout<<"size: "<<four_index;
	for(int i = 0 ; i <four_index ; i++){
		cout<<endl<<i<<endl;
		cout<<four_term[i].w;
		cout<<four_term[i].x;
		cout<<four_term[i].y;
		cout<<four_term[i].z;
	}*/
	Eight_map(four_term , four_index);
}
void Eight_map(K_map * f_term , int size){
	int psize = 500;
	K_map * buffer_term = new K_map[ psize ];
	K_map * eight_term = new K_map[ psize ];
	int eight_index = 0;
	int buffer_size = 0;
	for(int i = 0;i<psize;i++){
		eight_term[i].w = buffer_term[i].w=0;
		eight_term[i].x = buffer_term[i].x=0;
		eight_term[i].y = buffer_term[i].y=0;
		eight_term[i].z = buffer_term[i].z=0;
		buffer_term[i].if_along = true;
	} 
	if(size<6){
		for(int i=0 ; i<size ; i++){//檢查final關係
			final_term[f_index].w = f_term[i].w; 
			final_term[f_index].x = f_term[i].x; 
			final_term[f_index].y = f_term[i].y;
			final_term[f_index].z = f_term[i].z;
			f_index ++; 
		}
		return ;
	}
	for(int i = 0 ; i<size ; i++){  //1個bit一樣就合併;
		for(int j = 0 ; j<size ; j++){	
			f_term[i].same=0;  
			if(f_term[i].w !=-1 && f_term[i].w ==f_term[j].w){
				buffer_term[buffer_size].w = f_term[i].w;
				f_term[i].same++;
			}
			else buffer_term[buffer_size].w =-1;

			if(f_term[i].x !=-1 && f_term[i].x ==f_term[j].x){
				buffer_term[buffer_size].x = f_term[i].x;
				f_term[i].same++;
			}
			else buffer_term[buffer_size].x =-1;

			if(f_term[i].y !=-1 && f_term[i].y ==f_term[j].y){
				buffer_term[buffer_size].y = f_term[i].y;
				f_term[i].same++;
			}
			else buffer_term[buffer_size].y =-1;

			if(f_term[i].z !=-1 && f_term[i].z == f_term[j].z){
				buffer_term[buffer_size].z = f_term[i].z;
				f_term[i].same++;
			}
			else buffer_term[buffer_size].z =-1;
			//cout<<"Eight_SAME: "<<i<<"  "<<f_term[i].same<<endl;

			if(f_term[i].same == 1 )	buffer_size++;
			else{
				final_term[f_index].w = f_term[i].w; 
				final_term[f_index].x = f_term[i].x; 
				final_term[f_index].y = f_term[i].y;
				final_term[f_index].z = f_term[i].z;
				f_index++;
			}
		}
	}
	/*
	for(int i = 0 ; i <buffer_size+1 ; i++){
	cout<<endl<<i<<endl;
	cout<<buffer_term[i].w;
	cout<<buffer_term[i].x;
	cout<<buffer_term[i].y;
	cout<<buffer_term[i].z;
	}*/

	//開始把包好的丟進去
	for(int i = 0 ; i <buffer_size ; i++){

		buffer_term[i].same = 0;

		for(int j = i+1 ; j<buffer_size ; j++){
			if(		buffer_term[i].w == buffer_term[j].w
				&&	buffer_term[i].x == buffer_term[j].x
				&&	buffer_term[i].y == buffer_term[j].y
				&&	buffer_term[i].z == buffer_term[j].z)
				buffer_term[i].same++;
			if(buffer_term[i].same==6){
				for(int k=0 ; k<eight_index ; k++) 
					if(buffer_term[i].w == eight_term[k].w 
						&& buffer_term[i].x == eight_term[k].x 
						&& buffer_term[i].y == eight_term[k].y 
						&& buffer_term[i].z == eight_term[k].z){
							buffer_term[i].if_along = false;
							break;
					}
					if(buffer_term[i].if_along == true){   //化簡後結果
						eight_term[eight_index].w = buffer_term[i].w;
						eight_term[eight_index].x = buffer_term[i].x;
						eight_term[eight_index].y = buffer_term[i].y;
						eight_term[eight_index].z = buffer_term[i].z;
						eight_index++;
					}
			}
		}
	}
	/*
	cout<<"buffer:"<<endl;
	for(int i = 0 ; i <buffer_size+1 ; i++){
	cout<<endl<<i<<endl;
	cout<<buffer_term[i].w;
	cout<<buffer_term[i].x;
	cout<<buffer_term[i].y;
	cout<<buffer_term[i].z;
	}*/
	//cout<<"eight_term: "<<endl;
	for(int i = 0 ; i <eight_index ; i++){
		/*	
		cout<<endl<<i<<endl;
		cout<<eight_term[i].w;
		cout<<eight_term[i].x;
		cout<<eight_term[i].y;
		cout<<eight_term[i].z;
		*/
		final_term[f_index].w = eight_term[i].w;
		final_term[f_index].x = eight_term[i].x;
		final_term[f_index].y = eight_term[i].y;
		final_term[f_index].z =eight_term[i].z;
		f_index++;
	}
	//cout<<"final: ";

}

void out_put(K_map * final_term , int f_index){
	//cout<<"final:"<<endl;
	for(int i = 0 ; i <f_index ; i++){
		if(final_term[i].w == -1)
			cout<<2;
		else cout<<final_term[i].w;

		if(final_term[i].x == -1)
			cout<<2;
		else cout<<final_term[i].x;

		if(final_term[i].y == -1)
			cout<<2;
		else cout<<final_term[i].y;

		if(final_term[i].z == -1)
			cout<<2;
		else cout<<final_term[i].z;
		cout<<endl;
	}
}

int main(int argc, char const *argv[])
{
	ifstream input("Case1.txt");
	int count;
	int map[16];
	string str;
	//cin>>count;
	//cin>>str;
	//cout<<str;

	input>>count>>ws;
	for(int time = 0 ; time<count ; time++){
		getline(input, str);
		//cout<<str;
		map[0]=str[0]-'0';
		map[1]=str[1]-'0';
		map[2]=str[3]-'0';
		map[3]=str[2]-'0';
		map[4]=str[4]-'0';
		map[5]=str[5]-'0';
		map[6]=str[7]-'0';
		map[7]=str[6]-'0';
		map[8]=str[12]-'0';
		map[9]=str[13]-'0';
		map[10]=str[15]-'0';
		map[11]=str[14]-'0';
		map[12]=str[8]-'0';
		map[13]=str[9]-'0';
		map[14]=str[11]-'0';
		map[15]=str[10]-'0';

		for(int i=0 ; i<16 ; i++)
			cout<<map[i];
		pick_term(map);
		cout<<"# "<<time+1<<endl;
		out_put(final_term , f_index);
		cout<<endl;
	}
	system("pause");
	return 0;
}