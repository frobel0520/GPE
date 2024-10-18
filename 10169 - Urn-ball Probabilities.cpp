#include <bits/stdc++.h>

using namespace std;

double p[1000001];
int cnt[1000001];

void init()
{
    double ans = 1;
    p[0] = 1;
    cnt[0] = 0;
    for (long long i = 1; i <= N; i++) 
	{
        double t = 1.0 / (i * (i + 1));
        ans *= t;
        p[i] = (1 - t) * p[i - 1];

        cnt[i] = cnt[i - 1];
        while (ans < 1)
            ans *= 10, cnt[i]++;
    }
}

int main()
{
    init();

    int n;
    while (scanf("%d", &n)) 
	{
		printf("%f %d\n", 1 - p[n], cnt[n] - 1);
	}
    return 0;
}

