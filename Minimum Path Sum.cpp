#include <bits/stdc++.h>
using namespace std;

int main()
{
	int cases;
	cin >> cases;
	while(cases--)
	{
		int r, c;
		cin >> r >> c;
		int M[r][c];
		int DP[r][c];
		for(int i=0; i<r; i++)
		{
			for(int j=0; j<c; j++)
			{
				cin >> M[i][j];
			}
		}
		
		DP[0][0] = M[0][0];
		for(int i=1; i<r; i++) DP[i][0] = M[i][0] + DP[i-1][0];
		for(int j=1; j<c; j++) DP[0][j] = M[0][j] + DP[0][j-1];
		
		for(int i=1; i<r; i++)
		{
			for(int j=1; j<c; j++)
			{
				DP[i][j] = M[i][j] + min(DP[i-1][j], DP[i][j-1]);
			}
		}
		cout << DP[r-1][c-1] << endl;
	}
}
