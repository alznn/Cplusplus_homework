#include <iostream>
using namespace std;

int main(){
	int n = 0 , m = 0 ;
	while(cin>>n>>m){
		int sum = 0 , count = 1;
		for( ; ; n++){
			sum += n;
			if(sum <= m )
				++count;
			else break;
		}
		cout<<count<<endl;
	}
}