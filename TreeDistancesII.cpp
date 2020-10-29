#include <bits/stdc++.h>
using namespace std;

const int N = 200002;

vector<int> g[N];
int n;

void enter() 
{
    cin >> n;
    for (int i=1,u,v; i<n; ++i) 
    {
        cin >>u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

int cc[N];

long long r[N];
int d[N];

void dfs(int u, int p) 
{
    for (int v : g[u]) 
    {
        if (v == p) continue;
        d[v] = d[u] + 1;
        dfs(v, u);
        cc[u] += cc[v];
    }
    cc[u]++;
}

void dfs2(int u, int p) 
{
    for (int v : g[u]) 
    {
        if (v == p) continue;
        r[v] = r[u] + (n - cc[v]) - cc[v];
        dfs2(v, u);
    }
}

void solve() 
{
    dfs(1, 0);
    for (int i=1; i<=n; ++i) 
        r[1] += d[i];
    dfs2(1, 0);
    for (int i=1; i<=n; ++i) 
        cout << r[i] << " ";
}

int main() 
{
    enter();
    solve();
}