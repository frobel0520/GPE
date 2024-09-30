#include<bits/stdc++.h>
using namespace std;

int GCD(int a, int b)
{
	if(b == 0) return a;
	else return GCD(b, a % b);
}

int main()
{
	int cases;
	cin >> cases;
	cin.ignore();
	for(int i=0; i<cases; i++)
	{
		string s1, s2;
		cin >> s1;
		cin >> s2;
		
		int a, b;
		a = stoi(s1, nullptr, 2);
		b = stoi(s2, nullptr, 2);
		
		int g = GCD(a, b);
		cout << "Pair #" << i+1 << ": ";
		if(g == 1) cout << "Love is not all you need!" << endl;
		else cout << "All you need is love!" << endl;
	}
}
