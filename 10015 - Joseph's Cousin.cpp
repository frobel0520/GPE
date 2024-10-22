#include <bits/stdc++.h>
using namespace std;

bool prime[1000001];

int main()
{
	memset(prime, true, sizeof(prime));
	prime[0] = true;
	prime[1] = true;
	for(int i=2; i<1001; i++)
	{
		for(int j=i+i; j<1000001; j+=i)
		{
			prime[j] = false;
		}
	}
	
	vector<int> primes;
	for(int i=2; i<1000001; i++)
	{
		if(prime[i] == true) primes.push_back(i);
	}
	
	int n;
	while(cin >> n && n != 0)
	{
		vector<int> alive;
		for(int i=1; i<=n; i++) alive.push_back(i);
		
		int cur=0;
		for(int i=0; i<n-1; i++)
		{
			cur += primes[i]-1;
			cur %= alive.size();
			alive.erase(alive.begin() + cur);
		}
		cout << alive[0] << endl;
	}
}
