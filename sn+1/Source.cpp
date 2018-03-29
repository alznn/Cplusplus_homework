#include <iostream>
using namespace std;

int main()
{
	int i = 0 , j = 0 , max = 0;
	static int size[100];
	cin>>i>>j;
	for(int k = 0 ; k<j-i ; k++)
		size[k]=0;
	for(int start = i ,k = 0 ; start<j ; start++){
		int count = 1;
		int n=start;
		while(true){
			if(n==1)	break;
			if(n %2 == 0)
				n/=2;
			else
				n=n*3+1;
			count++;
		}
		if(count>max)
			max = count;
	}
	cout<<i<<" "<<j<<" "<<max;
	system("pause");
}