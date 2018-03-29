#include <iostream>
using namespace std;

int main(){
	int num = 0;
	while(cin>>num){
		if( 0 <= num && num <= 10 )
			cout<<num*6;
		else if( num >= 40 )
			cout<<"100";
		else if(10<num && num <= 20)
			cout<< 60 + (num-10)*2;
		else if( 20<num && num < 40 )
			cout<< 80 + (num-20);
		cout<<endl;
	}
}