#include <bits/stdc++.h>
using namespace std;

bool check(string s)
{
	if(s.length() == 1) return true;
	if(s.length() == 2) return s[0] == s[1];
	if(s.length() == 3) return s[0] == s[2];
	if(s.length() == 4) return (s[0] == s[3]) && (s[1] == s[2]);
}

int main()
{
	int cases;
	cin >> cases;
	while(cases--)
	{
		int hr, min;
		scanf("%d:%d", &hr, &min);
		while(1)
		{
			min++;
			if(min == 60)
			{
				hr++;
				min = 0;
			}
			if(hr == 24) hr = 0;
			
			stringstream ss;
			string str;
			ss << hr * 100 + min;
			ss >> str;
			
			if(check(str)) break;
		}
		if(hr < 10) printf("0");
		printf("%d", hr);
		printf(":");
		if(min < 10) printf("0");
		printf("%d\n", min);
	} 
}
