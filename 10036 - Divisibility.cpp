#include <bits/stdc++.h>
using namespace std;

int vec[10001];
bool DP[10001][101];

int main()
{
	int cases;
	cin >> cases;
	while(cases--)
	{
		memset(DP, false, sizeof(DP));
		DP[0][0] = true;
		
		int N, K;
		cin >> N >> K;
		
		for(int i=0; i<N; i++) 
		{
			cin >> vec[i];
			vec[i] = abs(vec[i]) % K;
		}
		
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<K; j++)
			{
				if(DP[i][j] == true)
				{
					DP[i+1][(j + vec[i] + K) % K] = true;
					DP[i+1][(j - vec[i] + K) % K] = true;
				}
			}
		}
		
		if(DP[N][0] == true) cout << "Divisible" << endl;
		else cout << "Not divisible" << endl;
	}
}
