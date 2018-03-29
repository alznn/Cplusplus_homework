/*#include <iostream>
using namespace std;
int main() 
{
int a,b;
while(cin>>a>>b)
{	
while (b&&(a%=b)&&(b%=a));
cout<<a+b<<endl;
}	
}
*/

#include <iostream>
using namespace std;

int main(){
	unsigned int x = 0, y = 0;
	//unsigned int gcd = 0;

	while(cin >> x >> y){
		while (y && (x%=y) && (y%=x));
		cout << x+y<<endl;
	}
	return 0;
}