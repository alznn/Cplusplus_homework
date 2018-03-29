#include <iostream>
using namespace std;
int main(){
	long long int num = 0;
	cin>>num;
	while(num!=0){
		//long long int num=0;
		if(num/10000000 > 0){
			cout<<num/10000000<<"kuit";
			num%=10000000;

		}
		if(num/100000 > 0){
			cout<<num/100000<<"lakh";
			num%=100000;}
		if(num/1000>0){
			cout<<num/1000<<"hajar";
			num%=1000;
		}
		if(num/100 > 0){
			cout<<num/100<<"shata";
			num%=100;
		}
		cout<<num;
		num = 0;
		cin>>num;
	}
	system("pause");
}