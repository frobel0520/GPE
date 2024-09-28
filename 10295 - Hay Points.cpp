#include <bits/stdc++.h>
using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;
	
    map<string, int> dict;
    string word;
    int point;
    
    for(int i=0; i<m; i++)
    {
	    cin >> word >> point;
	    dict[word] = point;
    }   
    
    for(int i=0; i<n; i++)
	{
		int ans = 0;
	    while(cin >> word && word != ".")
	    {
	  	    if(dict[word] > 0) ans += dict[word];
	    }
	    cout << ans << endl;
    }
    return 0;
}
