#include <bits/stdc++.h>
using namespace std;

bool prime[1000001];
vector<int> primes;
vector<int> digit_primes;
int ans[1000001];

void init()
{
	memset(prime, true, sizeof(prime));
	memset(ans, 0, sizeof(ans));
	prime[0] = false;
	prime[1] = false;
	// prime table
	for(int i=2; i<1001; i++)
	{
		if(prime[i] == true)
		{
			for(int j=i+i; j<1000001; j+=i) prime[j] = false;
		}
	}
	// prime list
	for(int i=2; i<1000001; i++)
	{
		if(prime[i] == true) primes.push_back(i);
	}
	// digit prime list
	for(int i=0; i<primes.size(); i++)
	{
		int sum = 0;
		int tmp = primes[i];
		while(tmp)
		{
			sum += tmp % 10;
			tmp /= 10;
		}
		if(prime[sum] == true) digit_primes.push_back(primes[i]);
	}
	int cnt = 0, idx = 0;
	for(int i=0; i<1000001; i++)
	{
		if(i == digit_primes[idx])
		{
			cnt++;
			idx++;
		}
		ans[i] = cnt;
	}
}

int main()
{
	init();
	
	int cases;
	scanf("%d", &cases);
	while(cases--)
	{
		int left, right;
		int idx = 0;
		scanf("%d %d", &left, &right);
		printf("%d\n", ans[right] - ans[left-1]);
	}
}
