#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	char a[1005];
	int length;
	while(cin>>a)
	{
		length=strlen(a);
		int i;
		for(i=0;i<length;i++)
		{
			if(a[i]!=a[length-1-i])
				break;
		}
		if(i<length)		
			cout<<"no"<<endl;
		else
			cout<<"yes"<<endl;
	}
	system("pause");
}