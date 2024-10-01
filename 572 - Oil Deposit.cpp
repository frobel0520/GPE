#include <bits/stdc++.h>
using namespace std;

char M[105][105] = {'x'};
bool visited[105][105] = {false};

void Visit(int u, int v)
{
	if(M[u][v] == '@' && visited[u][v] == false)
	{
		visited[u][v] = true;
		Visit(u-1, v-1);
		Visit(u-1, v);
		Visit(u-1, v+1);
		Visit(u, v-1);
		Visit(u, v+1);
		Visit(u+1, v-1);
		Visit(u+1, v);
		Visit(u+1, v+1);
	}
}

int main()
{
	int m, n;
	while(cin >> m >> n && m != 0)
	{
		for(int i=1; i<=m; i++)
		{
			for(int j=1; j<=n; j++)
			{
				cin >> M[i][j];
			}
		}
		
		for(int i=0; i<105; i++)
		{
			for(int j=0; j<105; j++)
			{
				visited[i][j] = false;
			}
		}
		
		int ans = 0;
		for(int i=1; i<=m; i++)
		{
			for(int j=1; j<=n; j++)
			{
				if(M[i][j] == '@' && visited[i][j] == false)
				{
					ans++;
					Visit(i, j);
				}
			}
		}
		cout << ans << endl;
	}
}
