#include <bits/stdc++.h>
using namespace std;

int depth, n , x, y;


void solve()
{
    while(true)
    {
        if(n == 1) return;

		// from depth k to depth k+1
        y++;
        n--;
        depth++;

        if(n == 1) return;

        for (int i = 0; i < depth -1; i++) {
            x--;
            y++;
            n--;
            if(n == 1) return;
        }

        for (int i = 0; i < depth; i++) {
            x--;
            n--;
            if(n == 1) return;
        }

        for (int i = 0; i < depth; i++) {
            y--;
            n--;
            if(n == 1) return;
        }

        for (int i = 0; i < depth; i++) {
            x++;
            y--;
            n--;
            if(n == 1) return;
        }

        for (int i = 0; i < depth; i++) {
            x++;
            n--;
            if(n == 1) return;
        }

        for (int i = 0; i < depth; i++) {
            y++;
            n--;
            if(n == 1) return;
        }
    }
}

int main()
{
    while(cin >> n)
    {
        depth = 0;
        x = 0;
        y = 0;

        solve();

        cout << x << " " << y << endl;
    }
    return 0;
}
