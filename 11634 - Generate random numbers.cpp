#include <bits/stdc++.h>
using namespace std;

int main()
{	
	int n;
	while(cin >> n && n != 0)
	{
		bool used[10001] = {false};
		int ans = 0;
		while(used[n] == false)
		{
			used[n] = true;
			ans++;
			n *= n;
			n /= 100;
			n %= 10000;
		}
		cout << ans << endl;
	}
}
