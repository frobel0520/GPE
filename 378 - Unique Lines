#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int gcd(int a, int b) {
	if(b == 0) return a;
	else return gcd(b, a % b);
}

int main()
{
	int cases, N;
	cin >> cases;
	
	for(int k=0; k<cases; k++)
	{
		cin >> N;
		vector<pii> points(N);
		
		for(int i=0; i<N; i++)
		{
			cin >> points[i].first >> points[i].second;
		}
		
		set<pair<pii, int> > uniqueLines;
		
		
		for(int i=0; i<N; i++)
		{
			for(int j=i+1; j<N; j++)
			{
				int dx, dy, g;
				dx = points[j].first - points[i].first;
				dy = points[j].second - points[i].second;
				g = gcd(dx, dy);
				
				dx = dx / g;
				dy = dy / g;
				
				// (-, +) -> (+, -)
				// (-, -) -> (+, +)
				// (0, -) -> (0, +)
				
				if(dx < 0 || (dx == 0 && dy < 0))
				{
					dx = -dx;
					dy = -dy;
				}
				
				// intercept = dy * x - dx * y;
				int intercept = dy * points[i].first - dx * points[i].second;
				
				uniqueLines.insert( { {dx, dy}, intercept} );
			}
		}
		cout << uniqueLines.size() << endl;	
	}
	return 0;
}
