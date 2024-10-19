#include<bits/stdc++.h>
using namespace std;
 
int DP[101][101];
 
int solve(int n, int m)
{
	int tmp;
	int ans = 0;
	int update = 0;
	
	for (int i=1; i<=n; i++)
	{
		for (int j=i; j<=n; j++)
		{
			tmp = 0;
			for (int k=1; k<=m; k++)
			{
				update = DP[j][k] - DP[i-1][k];
				
				if (tmp >= 0) tmp += update;
				else tmp = update;
				
				ans = max(ans, tmp);
			}
		}
	}
	return ans;
}
 
int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m))
	{
		if(n == 0 && m == 0) return 0;
		
		for (int i=1; i<=n; i++)
		{
			for (int j=1; j<=m; j++)
			{
				scanf("%d", &DP[i][j]);
				if(DP[i][j] == 1) DP[i][j] = -1000;
				else DP[i][j] = 1;
				
				DP[i][j] += DP[i-1][j];
			}
		}
		printf("%d\n", solve(n, m));
	}
	return 0;
}
