#include <bits/stdc++.h>
using namespace std;

int main()
{
	unsigned int n;
	while(cin >> n && n != 0)
	{
		unsigned int a = sqrt(n);
		if(a * a == n) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}
