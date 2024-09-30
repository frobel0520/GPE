#include<bits/stdc++.h>
using namespace std;

unordered_map<string, int> M;

int main()
{
	int N;
	while(cin >> N && N != 0)
	{
		cin.ignore();
		
		M.clear();
		int mx = 1;
		
		for(int i=0; i<N; i++)
		{
			string str;
			getline(cin, str);
			
			// read courses and sort
			stringstream ss(str);
			int set[5];
			for(int j=0; j<5; j++) ss >> set[j];
			sort(begin(set), end(set));
			
			// convert into strings
			string s = "";
			for(int j=0; j<5; j++) s += to_string(set[j]);
			
			// count appearance
			if(M.find(s) == M.end()) M[s] = 1;
			else
			{
				M[s]++;
				if(M[s] > mx) mx = M[s];
			}
		}
		
		// output answer
		if(mx == 1) cout << N << endl;
		else
		{
			int ans = 0;
			for(auto i: M)
			{
				if(i.second == mx) ans += mx;
			}
			cout << ans << endl;
		}
	}
}
