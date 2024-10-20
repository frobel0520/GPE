#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	int cases = 0;
	while(cin >> s)
	{
		cases++;
		cout << "Case " << cases << ":" << endl;
		int len = s.length();
		int DP[len];
		memset(DP, 0, sizeof(DP));
		DP[0] = 1;
		
		char ch;
		int match = 1;
		for(int i=1; i<len; i++)
		{
			if(s[i] == s[i-1]) 	match++;
			else match = 1;
			DP[i] = match;
		}
		
		int num;
		cin >> num;
		while(num--)
		{
			int i, j;
			cin >> i >> j;
			int left = min(i, j);
			int right = max(i, j);
			if(DP[right] >= right - left + 1) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	}
	
}
