#include <bits/stdc++.h>
using namespace std;

int main()
{
	string str1, str2;
	while(getline(cin, str1) && getline(cin, str2))
	{
		int left[26] = {0};
		int right[26] = {0};
		
		for(int i=0; i<str1.length(); i++) left[str1[i] - 'a']++;
		for(int i=0; i<str2.length(); i++) right[str2[i] - 'a']++;
		
		string ans = "";
		for(int i=0; i<26; i++)
		{
			if(left[i] && right[i])
			{
				int N = min(left[i], right[i]);
				for(int j=0; j<N; j++) ans += char(i + 'a');
			}
		}
		cout << ans << endl;
	}
}
