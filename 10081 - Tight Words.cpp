#include <bits/stdc++.h>
using namespace std;

double DP[101][10];

int main()
{
	int k, n;
	while(cin >> k >> n)
	{
		// first step
		for(int i=0; i<=k; i++)
		{
			DP[1][i] = 1.0 / (k+1);
		}
		
		for(int i=2; i<=n; i++)
		{
			for(int cur=0; cur<=k; cur++)
			{
				DP[i][cur] = 0.0;
				for(int prev=0; prev<=k; prev++)
				{
					if(abs(cur - prev) <= 1)
					{
						DP[i][cur] += DP[i-1][prev] * 1.0 / (k+1);
					}
				}
			}
		}
		double sum = 0.0;
		for(int i=0; i<=k; i++) sum += DP[n][i];
		printf("%.5lf\n", sum * 100);	
	}
}
