#include <bits/stdc++.h>
using namespace std;

int main()
{
	int S;
	long long D;
	while(cin >> S >> D)
	{
		while(D > S)
		{
			D -= S;
			S++;
		}
		cout << S << endl;
	}
}
