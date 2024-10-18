#include <bits/stdc++.h>
using namespace std;

int DP[27][27][352]; /*[letter][length][sum]*/

void build() 
{
    int i, j, k;
    memset(DP, 0, sizeof(DP));
    DP[0][0][0] = 1;
    
    for(i = 1; i <= 26; i++) 
	{
        for(j = 0; j <= i; j++) 
		{
            for(k = 0; k < 352; k++) 
			{
                DP[i][j][k] = DP[i-1][j][k];
                if(j > 0 && k >= i)
                DP[i][j][k] += DP[i-1][j-1][k-i];
            }
        }
    }
}

int main() 
{
    build();
    int L, S;
    int cases = 1;
    while(cin >> L >> S) 
	{
        if(L == 0 && S == 0) break;
        
        if(L > 26 || S > 351) cout << "Case " << cases << ": 0" << endl;
		else cout << "Case " << cases << ": " << DP[26][L][S] << endl;
		
		cases++;
    }
    return 0;
}
