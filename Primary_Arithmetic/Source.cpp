#include <iostream>
using namespace std;

int main(){
	long long unsigned int num1=0 , num2=0;
	cin>>num1>>num2;
	while(num1!=0 || num2!=0){
		int count=0;
		for(int i=0 , j = 0 ; num1>1 && num2>1; num1/=10 , num2/=10){
			i=num1 ; j=num2;
			if((i%10 + j%10) > 9){
				count++;
			}
		}
		if(count == 0)
			cout<<"No carry operation.";
		else if(count == 1)
			cout<<"1 carry operation.";
		else
			cout<<count<<" carry operations.";
		num1=0 ; num2=0;
		cin>>num1>>num2;;
	}
	system("pause");
}