#include <bits/stdc++.h>
using namespace std;

char str[10005];
int int_str[10005];

int solve(int* s, int len) 
{
    int idx1 = 0, idx2 = 1;
    int match = 0;
    while (1) 
	{
		if(match >= len || idx1 >= len || idx2 >= len) break;
		
		int left, right;
		left = (idx1 + match) % len;
		right = (idx2 + match) % len;
		
        if (s[left] == s[right]) match++;
        else 
		{
        	if(s[left] > s[right]) idx1 = idx1 + match + 1;
			else idx2 = idx2 + match + 1;
			
            if (idx1 == idx2) idx1++;
            match = 0;
        }
    }
    idx1 = min(idx1, idx2);
    return idx1 + 1;
}

int main() 
{
	int cases;
	int len;
    cin >> cases;
    while (cases--) 
	{
        scanf("%s", str);
        len = strlen(str);
        for (int i = 0; i < len; i++) int_str[i] = str[i] - 'a';
        
        int ans = solve(int_str, len);
        printf("%d\n", ans);
    }
    return 0;
}

