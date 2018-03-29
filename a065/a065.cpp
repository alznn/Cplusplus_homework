#include <iostream>
#include<cstdlib>
using namespace std;

int main(){
	char hint[8];
	int pw[6];
	while(cin>>hint){
		for(int i=0 ; i<6 ; i++)
			pw[i] = 0;
		for(int i =6 ; i>=1 ; i--)
			pw[i-1]=abs(hint[i]-hint[i-1]);
		for(int i=0 ; i<6 ; i++)
			cout<<pw[i];
		cout<<endl;
	}
	system("pause");
}