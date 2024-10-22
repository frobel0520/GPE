#include <bits/stdc++.h>
using namespace std;

int val[6] = {1, 2, 4, 10, 20, 40};

int main()
{
	int change[1001];
	memset(change, 0, sizeof(change));
	for(int n=0; n<1001; n++)
	{
		int cnt = 0;
		int tmp = n;
		for(int i=5; i>=0; i--)
		{
			if(tmp >= val[i])
			{
				int num = tmp / val[i];
				cnt += num;
				tmp -= val[i] * num;
			}
			if(tmp == 0) break;	
		}
		change[n] = cnt;
	}
	
	int coins[6];
	int a, b, price;
	char ch;
	while(cin >> coins[0] >> coins[1] >> coins[2] >> coins[3] >> coins[4] >> coins[5])
	{
		if(coins[0] + coins[1] + coins[2] + coins[3] + coins[4] + coins[5] == 0) return 0;
		
		cin >> a >> ch >> b;
		price = a * 100 + b;
		price /= 5;
		
		int total = 0;
		for(int i=0; i<6; i++) total += coins[i] * val[i];
		
		int give[1001];
		for(int i=0; i<1001; i++) give[i] = 100000;
		give[0] = 0;
		
		for(int i=0; i<6; i++)
		{
			for(int j=1; j<=coins[i]; j++)
			{
				int base = j * val[i];
				for(int k=total; k>=base; k--)
				{
					give[k] = min(give[k], give[k-base] + j);
				}
			}
		}
		
		int ans = give[price];
		for(int i=price+1; i<101; i++) ans = min(ans, give[i] + change[i-price]);
		cout << setw(3) << ans << endl;
	}
}
