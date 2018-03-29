#include <iostream>
#include <string>
using namespace std;

int main(){
	string num;
	cin>>num;
	while(num != "0"){
		int sum1 = 0 , sum2 = 0;
		for(int i = 0 ; i<num.size() ; i++){
			if( i % 2 == 0)
				sum2+=num[i]-'0';
			else
				sum1+=num[i]-'0';
		}
		if(sum2-sum1==0 || (sum2-sum1) % 11 == 0 )
			cout<<num<<"is a multiple of 11."<<endl;		else			cout<<num<<"is not a multiple of 11."<<endl;
		cin>>num;
	}
	return 0;
}