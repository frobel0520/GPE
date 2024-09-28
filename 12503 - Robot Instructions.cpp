#include <bits/stdc++.h>
using namespace std;

int ins[101] = {0};

int Move(string s, int &j)
{
	if(s[0] == 'L')
	{
		ins[j] = -1;
		return -1;
	}
	else if(s[0] == 'R')
	{
		ins[j] = 1;
		return 1;
	}
	else
	{
		string ss;
		cin >> ss;
		int idx;
		cin >> idx;
		
		ins[j] = ins[idx-1];
		return ins[idx-1];
	}
}

int main()
{
	int cases, N;
	string s = "";
	cin >> cases;
	for(int i=0; i<cases; i++)
	{
		cin >> N;
		int pos = 0;
		for(int j=0; j<N; j++)
		{
			cin >> s;
			pos += Move(s, j);
		}
		for(int j=0; j<101; j++)
		{
			ins[j] = 0;
		}
		cout << pos << endl;
	}
	return 0;
}
