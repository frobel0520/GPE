#include<bits/stdc++.h>
using namespace std;

int main()
{
	int N;
	while(cin >> N)
	{
		int full=N, drank=0, empty=0;
		while(full > 0)
		{
			drank += full;
			empty += full;
			full = empty / 3;
			empty = empty % 3;
		}
		
		if(empty == 2) drank++;
		cout << drank << endl;
	}
	return 0;
}
