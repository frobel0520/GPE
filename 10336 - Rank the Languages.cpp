#include <bits/stdc++.h>
using namespace std;

char M[20][20];
bool visited[20][20];

void Visit(int u, int v)
{
	visited[u][v] = true;
	if(M[u-1][v] == M[u][v] && visited[u-1][v] == false) Visit(u-1, v);
	if(M[u+1][v] == M[u][v] && visited[u+1][v] == false) Visit(u+1, v);
	if(M[u][v-1] == M[u][v] && visited[u][v-1] == false) Visit(u, v-1);
	if(M[u][v+1] == M[u][v] && visited[u][v+1] == false) Visit(u, v+1);
}

int main()
{
	int cases;
	cin >> cases;
	for(int k=0; k<cases; k++)
	{
		for(int i=0; i<20; i++)
		{
			for(int j=0; j<20; j++)
			{
				M[i][j] = '.';
				visited[i][j] = false;
			}
		}
		
		int m, n;
		cin >> m >> n;
		for(int i=0; i<m; i++)
		{
			for(int j=0; j<n; j++)
			{
				cin >> M[i][j];
			}
		}
		
		int mx = 0;
		int cnt[26] = {0};
		for(int i=0; i<m; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(!visited[i][j])
				{
					int letter = M[i][j] - 'a';
					cnt[letter]++;
					if(cnt[letter] > mx) mx = cnt[letter];
					Visit(i, j);
				}
			}
		}
		
		cout << "World #" << k+1 << endl;
		for(int i=mx; i>0; i--)
		{
			for(int j=0; j<26; j++)
			{
				if(cnt[j] == i) cout << char(j + 'a') << ": " << i << endl;
			}
		}
	}
	return 0;
}
