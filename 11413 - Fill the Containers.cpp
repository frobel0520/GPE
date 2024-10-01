#include <bits/stdc++.h>
using namespace std;

bool CanDistribute(vector<int>& vessels, int m, int capacity)
{
	int containers = 1;
	int currentVessel = 0;
	for(int v: vessels)
	{
		if(currentVessel + v > capacity)
		{
			containers++;
			currentVessel = v;
		}
		else
		{
			currentVessel += v;
		}
		if(containers > m) return false;
	}
	return true;
}


int main()
{
	int n, m;
	while(cin >> n >> m)
	{
		vector<int> vessels(n);
		int left=0, right=0;
		
		for(int i=0; i<n; i++)
		{
			cin >> vessels[i];
			left = max(left, vessels[i]);
			right += vessels[i];
		}
		
		// binary search
		while(left < right)
		{
			int mid = left + (right - left) / 2;
			if(CanDistribute(vessels, m, mid))
			{
				right = mid;
			}
			else
			{
				left = mid + 1;
			}
		}
		cout << left << endl;
	}
}
