#include <bits/stdc++.h>
using namespace std;

int main()
{
	int fibs[51];
	fibs[0] = 1;
	fibs[1] = 1;
	for(int i=2; i<51; i++)
	{
		fibs[i] = fibs[i-1] + fibs[i-2];
	}
	int n;
	while(cin >> n && n != 0)
	{
		cout << fibs[n] << endl;
	}
}
