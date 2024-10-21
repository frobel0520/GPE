#include <bits/stdc++.h>
using namespace std;

string testcase;
string submit;

int main()
{
	int n;
	int cnt = 0;
	while(cin >> n && n != 0)
	{
		cnt++;
		testcase = "";
		getchar();
		
		string str;
		for(int i=0; i<n; i++)
		{
			getline(cin, str);
			testcase += str;
			if(i != n-1) testcase += "\n";
		}
		//cout << "Testcase: " << testcase << endl;
		
		int m;
		cin >> m;
		submit = "";
		getchar();
		
		for(int i=0; i<m; i++)
		{
			getline(cin, str);
			submit += str;
			if(i != m-1) submit += "\n";
		}
		//cout << "Submit: " << submit << endl;
		
		
		cout << "Run #" << cnt << ": ";
		
		bool ac = true;
		if(testcase == submit)
		{
			cout << "Accepted" << endl;
			continue;
		}
		
		bool pe = true;
		for(int i=0; i<testcase.length(); i++)
		{
			if(isdigit(testcase[i]) == false)
			{
				testcase.erase(i, 1);
				i--;
			}
		}
		
		for(int i=0; i<submit.length(); i++)
		{
			if(isdigit(submit[i]) == false)
			{
				submit.erase(i, 1);
				i--;
			}
		}
		
		if(testcase == submit)
		{
			cout << "Presentation Error" << endl;
			continue;
		}
		
		cout << "Wrong Answer" << endl;	
	}
}
