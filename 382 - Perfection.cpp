#include <bits/stdc++.h>
using namespace std;
string blanks[5] = {"", " ", "  ", "   ", "    "};

int main()
{	
	cout << "PERFECTION OUTPUT" << endl;
	
	int N;
	while(cin >> N && N != 0)
	{
		stringstream ss;
		string str;
		ss << N;
		ss >> str;
		cout << blanks[5 - str.length()] << N << "  ";
		
		int sum = 0;
		for(int i=1; i<=N/2; i++)
		{
			if(N % i == 0) sum += i;
		}
		if(sum < N) cout << "DEFICIENT" << endl;
		if(sum == N) cout << "PERFECT" << endl;
		if(sum > N) cout << "ABUNDANT" << endl;
	}
	
	cout << "END OF OUTPUT" << endl;
}
