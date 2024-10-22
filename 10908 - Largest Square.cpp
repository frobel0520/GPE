#include <bits/stdc++.h>
using namespace std;


int main()
{
	int cases;
	cin >> cases;
	while(cases--)
	{
		int row, col, num;
		cin >> row >> col >> num;
		cout << row << " " << col << " " << num << endl;
		
		char M[row][col];
		
		for(int i=0; i<row; i++)
		{
			for(int j=0; j<col; j++)
			{
				cin >> M[i][j];
			}
		}
		
		for(int i=0; i<num; i++)
		{
			int cx, cy;
			cin >> cx >> cy;
			char ch = M[cx][cy];
			
			int ans = 1;
			int r = 1;
			bool valid = true;
			while(cx-r >= 0 && cx+r < row && cy-r >=0 && cy+r < col)
			{
				for(int x=cx-r; x<=cx+r; x++)
				{
					if(valid == false) break;
					for(int y=cy-r; y<=cy+r; y++)
					{
						if(valid == false) break;
						if(M[x][y] != ch) valid = false;
					}
				}
				if(valid == true)
				{
					r++;
					ans += 2;	
				}
				else break;
			}
			cout << ans << endl;
		}
	}
}
