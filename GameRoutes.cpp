#include <bits/stdc++.h>
using namespace std;

const int N = 100002, mod = 1000000007;
vector<int> g[N];
int f[N];

int F(int u) 
{
    if (u == 1) 
        return 1;
    if (f[u]) 
        return f[u];
    for (int v : g[u]) 
    {
        f[u] = (f[u] + F(v)) % mod;
    }
    return f[u];
}

int n, m;

int main() 
{
    cin >> n >> m;
    for (int i=1, u, v; i<=m; ++i) 
    {
        cin >> u >> v;
        g[v].push_back(u);
    }
    cout << F(n);
}