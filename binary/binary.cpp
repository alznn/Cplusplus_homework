#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n=0,k;
	int a[100];
	while(cin>>n)
	{
		for(k=0;n>0;k++)
		{
			a[k]=n%2;
			n=n/2;
		}
		for(int i=k-1;i>=0;i--)
			cout<<a[i];
		cout<<endl;
	}
	
}