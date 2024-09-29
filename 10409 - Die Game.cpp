#include<bits/stdc++.h>
using namespace std;

enum directions {top, north, west, east, south, bottom};
int dice[6] = {1, 2, 3, 4, 5, 6};

void Roll(string str)
{
	int tmp = dice[top];
	if(str == "north")
	{
		dice[top] = dice[south];
		dice[south] = dice[bottom];
		dice[bottom] = dice[north];
		dice[north] = tmp;
	}
	else if(str == "south")
	{
		dice[top] = dice[north];
		dice[north] = dice[bottom];
		dice[bottom] = dice[south];
		dice[south] = tmp;
	}
	else if(str == "east")
	{
		dice[top] = dice[west];
		dice[west] = dice[bottom];
		dice[bottom] = dice[east];
		dice[east] = tmp;
	}
	else if(str == "west")
	{
		dice[top] = dice[east];
		dice[east] = dice[bottom];
		dice[bottom] = dice[west];
		dice[west] = tmp;
	}
	else return;
}

int main()
{
	// top, north, west, bottom, south, east

	int N;
	while(cin >> N && N != 0)
	{
		for(int i=0; i<6; i++) dice[i] = i+1;
		
		string str;
		for(int i=0; i<N; i++)
		{
			cin >> str;
			Roll(str);
		}
		cout << dice[top] << endl;
	}
	return 0;
}
