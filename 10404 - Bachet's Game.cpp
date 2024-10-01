#include <bits/stdc++.h>
using namespace std;

bool dp[1000005];
int steps[10];

int main()
{
	int n, m;
	
	while(cin >> n >> m)
	{		
		memset(dp, false, sizeof(dp));
		memset(steps, 0, 10);
		
		for(int i=0; i<m; i++) cin >> steps[i];
		
		for(int i=1; i<=n; i++)
		{
			for(int j=0; j<m; j++)
			{
				// legal step and opponent can't win
				if(i - steps[j] >= 0 && dp[i - steps[j]] == false)
				{
					dp[i] = true;
					break;
				}
			}
		}
		if(dp[n]) cout << "Stan wins" << endl;
		else cout << "Ollie wins" << endl;
	}
	
	return 0;
}
