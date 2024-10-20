#include <bits/stdc++.h>
using namespace std;

int main()
{
	int fact_digit_sum[1001] = {1, 1};
	int nums[3000] = {1};
	int digits = 1;
	
	for(int i=2; i<1001; i++)
	{
		for(int j=0; j<digits; j++)
		{
			nums[j] *= i;
		}
		
		for(int j=0; j<digits; j++)
		{
			nums[j+1] += nums[j] / 10;
			if(nums[j+1] > 0 && j+1 >= digits) digits++;
			nums[j] %= 10;
			fact_digit_sum[i] += nums[j];
		}
	}
	
	int n;
	while(cin >> n)
	{
		cout << fact_digit_sum[n] << endl;
	}
}
