#include <iostream>
using namespace std;

int main ()
{
	int amst[200];
	int first = 0 ,end = 0 ;

	while(cin>>first>>end){
		//cout<<first<<"  "<<end;
		int size = 0;
		for(int j=0 ; j<200 ; j++)
			amst[j]=0;
		
		for(int i=first;i<=end;i++)
		{
			int k=0;
			double sum=0;
			if(0<i && i<10){
				for(int j=i;j>=1;j=j/10)
				{
					k=j%10;
					sum+=k;
				}
			}
			else if(10 <= i && i<100)
			{
				for(int j=i;j>=1;j=j/10)
				{
					k=j%10;
					sum+=pow(k,2);
				}
			}
			else if(100 <= i && i < 1000)
			{
				for(int j=i;j>=1;j=j/10)
				{
					k=j%10;
					sum+=pow(k,3);
				}
			}

			else if(1000 <= i && i<10000)
			{
				for(int j=i;j>=1;j=j/10)
				{
					k=j%10;
					sum+=pow(k,4);
				}
			}

			else if(10000 <=i && i<100000)
			{
				for(int j=i;j>=1;j=j/10)
				{
					k=j%10;
					sum+=pow(k,5);
				}
			}

			else if(100000 <= i && i <1000000)
			{
				for(int j=i;j>=1;j=j/10)
				{
					k=j%10;
					sum+=pow(k,6);
				}
			}

			if(sum==i){
				amst[size]=sum;
				size++;
			}
		}
		if(amst[0]==0)
			cout<<"none";
		else
			for(int i = 0 ; i<size ; i++){
				cout << amst[i]<<" ";
			}
			cout<<endl;
	}
	system("pause");
}