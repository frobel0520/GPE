#include<bits/stdc++.h>
using namespace std;

void solve(vector<int>& weights)
{
	int sum = 0;
	for(auto i: weights) sum += i;
	if(sum % 2 == 1) 
	{
		cout << "NO" << endl;
		return;
	}
	
	bool dp[201] = {false};
	dp[0] = true;
	for(auto i: weights)
	{
		for(int k=200; k>=0; k--)
		{
			if(dp[k] == true) dp[k+i] = true;
		}
	}
	if(dp[sum / 2] == true) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main()
{
	int cases;
	cin >> cases;
	cin.ignore();
	
	while(cases--)
	{
		string str;
		getline(cin, str);
		
		int w;
		vector<int> weights;
		stringstream ss(str);
		while(ss >> w) weights.push_back(w);
		
		sort(weights.begin(), weights.end());
		solve(weights);
	}
}
