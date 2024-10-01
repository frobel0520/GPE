#include <bits/stdc++.h>
using namespace std;

int main()
{
	// 1^1, 2^2, 3^3, ... , 20^20;
	int tails[20] = {1, 4, 7, 6, 5, 6, 3, 6, 9, 0, 
					 1, 6, 3, 6, 5, 6, 7, 4, 9, 0};
	int table[20] = {0};
	
	// N = 0 ~ 19
	for(int i=0; i<20; i++)
	{
		for(int j=0; j<i; j++)
		{
			table[i] += tails[j];
		}
		table[i] %= 10;
	}
	
	// N = 0 ~ 99
	int ans[100] = {0};
	for(int i=0; i<100; i++)
	{
		int d, r, x;
		d = i / 20;
		r = i % 20;
		x = table[r] + 4 * d;
		ans[i] = x % 10;
	}

	
	string str;
	while(cin >> str && str != "0")
	{
		int val;
		if(str.size() < 3) 
		{
			val = stoi(str);
		}
		else
		{
			string s = str.substr(str.size()-2, 2);
			val = stoi(s);
		}
		cout << ans[val] << endl;
	}
	return 0;
}
