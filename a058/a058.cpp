#include <iostream>
using namespace std;

int main(){
	int count=0;
	int test[100] , mod[3];
	while(cin>>count){
		for(int i=0 ; i<3 ;i++)
			mod[i]=0;
		for(int i=0 ; i<count ; i++){
			test[i]=0;
			cin>>test[i];
		}
		for(int i=0 ; i<count ;i++){
			int nmod=0;
			nmod = test[i]%3;
			if( nmod == 0 )
				mod[0]++;
			else if( nmod == 1)
				mod[1]++;
			else
				mod[2]++;
		}
		for(int i=0 ; i<3 ;i++)
			cout<<mod[i]<<" ";
		cout<<endl;
	}
}