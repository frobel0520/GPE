#include <bits/stdc++.h>
using namespace std;

int main()
{
	double r;
	double pi = 3.141592653589;
	
	while(cin >> r && r != EOF)
	{
		double x, y, z;
		// square = x + 4y + 4z
		// circle = x + 3y + 2z
		z = r * r * (1 - sqrt(3.0)/4 - pi/6);
		y = r * r * (sqrt(3.0)/2 - 1 + pi/12);
		x = r * r * (1 - sqrt(3.0) + pi/3);
		printf("%.3lf %.3lf %.3lf\n", x, 4*y, 4*z);
	}
}
