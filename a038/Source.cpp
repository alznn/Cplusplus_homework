#include <iostream>
#include <vector>
using namespace std;

int main(){
	long long int num;
	//	vector <int>myvec;
	while( cin>>num){
		if(num==0)
			cout<<0;
		while (num%10==0&&num>0)
		{
			num/=10;
		}
		for(;num>0;num/=10)
			cout<<num%10;
		cout<<endl;
	}
	system("pause");
}