#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> arr(n);
	for(int i=0; i<n; i++)
	{
		cin >> arr[i];
	}
	
	vector<int> DP(n, 1);
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<i; j++)
		{
			if(arr[j] < arr[i])
			{
				DP[i] = max(DP[i], DP[j]+1);
			}
		}
	}
	int mx = *max_element(DP.begin(), DP.end());
	cout << mx << endl;
}
