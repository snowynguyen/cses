#include <bits/stdc++.h>
using namespace std;

const int N = 1000001, mod = 1000000007;
long long f[N], g[N];

int main() 
{
    f[1] = g[1]  = 1;
    for (int i=2; i<N; ++i) 
    {
        f[i] = (g[i-1] + f[i-1] * 4) % mod;
        g[i] = (f[i-1] + g[i-1] * 2) % mod;
    }

    int t; cin >> t;
    while (t--) 
    {
        int x; cin >> x;
        cout << (f[x] + g[x]) % mod << '\n';
    }
}