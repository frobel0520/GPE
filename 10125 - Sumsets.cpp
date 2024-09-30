#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& vec)
{
	for(int x=vec.size()-1; x>=0; x--)
	{
		for(int i=0; i<vec.size(); i++)
		{
			for(int j=i+1; j<vec.size(); j++)
			{
				for(int k=j+1; k<vec.size(); k++)
				{
					if(vec[i] + vec[j] + vec[k] == vec[x] && x != i && x != j && x != k)
					{
						return vec[x];
					}
				}
			}
		}
	}
	return INT_MIN;
}

int main()
{
	int N;
	while(cin >> N && N != 0)
	{
		vector<int> vec(N);
		for(int i=0; i<N; i++) cin >> vec[i];
		sort(vec.begin(), vec.end());
		
		long long ans = solve(vec);
		
		if(ans == INT_MIN) cout << "no solution" << endl;
		else cout << ans << endl;
	}
}
