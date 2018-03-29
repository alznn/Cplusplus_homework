#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int a= 0,b= 0,c=0,k=0,i=0;

	while(cin>>a>>b>>c)
	{
		k=(-b+sqrt(b*b-4*a*c))/(2a);
		i=(-b-sqrt(b*b-4*a*c))/(2a);

		if((b*b-4*a*c)>0)
				cout<<"Two different roots x1="<<k<<",x2="<<i<<endl;
				
		else if((b*b-4*a*c)==0)
				cout<<"Two same roots x="<<k<<endl;
	
		else if((b*b-4*a*c)<0)
			cout<<"No real roots"<<endl;
	}

	system("pause");
}