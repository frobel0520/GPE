#include <bits/stdc++.h>
using namespace std;

int mx[5] = {0, 10, 100, 1000, 10000};
vector<string> vec;
string zeros[4] = {"", "0", "00", "000"};

void solve(int k)
{
	for(int i=0; i<mx[k]; i++)
	{
		for(int j=0; j<mx[k]; j++)
		{
			if((i+j) * (i+j) == i*mx[k] + j)
			{
				stringstream ss, ss2;
				string left, right;
				ss << i;
				ss >> left;
				if(left.length() < k) left = zeros[k-left.length()] + left;
				ss2 << j;
				ss2 >> right;
				if(right.length() < k) right = zeros[k-right.length()] + right;
				
				vec.push_back(left + right);
			}
		}
	}
}

int main()
{
	int n;
	while(scanf("%d", &n) != EOF)
	{	
		vec.clear();
		solve(n/2);
		for(auto i: vec) cout << i << endl;
	}
}
