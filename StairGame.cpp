#include <bits/stdc++.h>
using namespace std;

int main() 
{
    ios_base::sync_with_stdio(0);
    int T; cin >> T;
    while (T--) 
    {
        int n; cin >> n;
        int xr = 0, x;
        for (int i=0; i<n; ++i) 
        {
            cin >> x;
            if (i & 1) 
                xr ^= x;
        }
        cout << ((xr != 0) ? "first\n" : "second\n");
    }
}