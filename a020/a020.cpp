#include <iostream>
#include <cstring>
using namespace std;
int main(){
	int Fid [26] = {10,11,12,13,14,15,16,17,34,18,19,20,21,22,35,23,24,25,26,27,28,29,32,30,31,33};
	char id[11] ;

	while(	cin>>id ){
		int sum = 0 , Fnum=0 , num =0;
		if(strlen(id)==10){

			Fnum = Fid[id[0]-'A'];
			sum+=(Fnum/10)+(Fnum%10)*9;

			for(int i=9 ; i>1 ; i--){
				num = id[10-i]-48;
				sum+=num*(i-1);
			}
			sum+=(id[9]-48);

			if(sum%10 == 0)
				cout<<"real";
			else
				cout<<"fake";
		}
		else
			cout<<"fake";
		cout<<endl;
	}
	system("pause");
	return 0;
}
