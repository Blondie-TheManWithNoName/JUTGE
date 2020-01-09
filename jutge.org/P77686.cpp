#include <iostream>
using namespace std;

bool es_capicua(int n) {
	int r,c,b = 0;
	c = n;
	while (c>0)
	{
		r = c % 10;
		c = c/10;
		b = b * 10 + r;
	}
	if (b == n)
		n = 1;
	else
		n = 0;
	return n;
}
int main() {

	int x,y;

	while(cin>>x)
	{
		y = es_capicua(x);
		if (y==1)
			cout<<"es_capicua("<<x<<") ? true"<<endl;
		else
			cout<<"es_capicua("<<x<<") ? false"<<endl;
	}
}
