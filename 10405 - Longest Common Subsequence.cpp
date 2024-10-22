#include <bits/stdc++.h>
using namespace std;

int main()
{
	string str1, str2;
	while(getline(cin, str1) && getline(cin, str2))
	{
		int L1 = str1.length();
		int L2 = str2.length();
		 
		int DP[L1+1][L2+1];
		memset(DP, 0, sizeof(DP));
		
		for(int i=1; i<=L1; i++)
		{
			for(int j=1; j<=L2; j++)
			{
				if(str1[i-1] == str2[j-1]) 
				{
					DP[i][j] = DP[i-1][j-1] + 1;
				}
				else
				{
					DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
				}
			}
		}
		
		cout << DP[L1][L2] << endl;
	}
}
