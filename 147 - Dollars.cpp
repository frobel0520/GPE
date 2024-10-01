#include <bits/stdc++.h>
using namespace std;

int coins[11] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

int main()
{
	long long dp[30003] = {0};
	dp[0] = 1;
	for(int i=0; i<11; i++)
	{
		for(int j=coins[i]; j<=30000; j++)
		{
				dp[j] = dp[j] + dp[j-coins[i]];
		}
	}
	
	int a, b;
	char p;
	int val;
	
	while(scanf("%d.%d", &a, &b) != EOF && (a != 0 || b != 0)) 
	{
		val = a * 100 + b;
		printf("%3d.%02d%17lld\n", a, b, dp[val]);
	}
	return 0;
}
