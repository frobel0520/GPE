#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N;
	while(cin >> N && N != 0)
	{
		int states[N];
		int curState;
		int terminated;
		for(int i=1; i<N; i++)
		{			
			curState = 0;
			terminated = 0;
			for(int k=0; k<N; k++) states[k] = 1;
			
			while(terminated < N) {
				if(curState == 12) break;

				states[curState] = 0;
				terminated++;
				//cout << curState << ' ';
				
				// jumping
				int cnt = 0;
				while(cnt < i)
				{
					curState++;
					curState %= N;
					if(states[curState] == 1)
					{
						cnt++;
					}
					else
					{
						// ignore
					}
				}
			}
			if(terminated == N-1) 
			{		
				cout << i << endl;
				break;
			}
			//cout << endl;
		}
	}
}
