#include <bits/stdc++.h>
using namespace std;

const int N = 200002;

#define lint long long 
int lt[N], rt[N], pos[N];
int n,q;
int a[N];
vector<int> g[N];
int ttime = 0;
lint s[N];

struct TSegmentTree 
{
    lint f[N * 4];

    void init(int id = 1, int l = 1, int r = n)
    {
        if (l == r) 
            f[id] = s[l];
        else 
        {
            int m = (l + r) / 2;
            init(id * 2, l, m);
            init(id * 2 + 1, m+1, r);
            f[id] = 0;
        }
    }

    void update (int id, int l, int r, int u, int v, lint w) 
    {
        if (r < u || v < l) 
            return;
        if (u <= l && r <= v) 
            f[id] += w;
        else 
        {
            int m = (l + r) / 2;
            update(id * 2, l, m, u, v, w);
            update(id * 2 + 1, m+1, r, u, v, w);
        }
    }

    lint get(int id, int l, int r, int p) 
    {
        if (r < p || p < l) 
            return 0;
        if (l == r) 
            return f[id];
        int m = (l + r)/2;
        return f[id] + get(id * 2, l, m, p) + get(id * 2 + 1, m+1, r, p);
    }
}it;

void dfs(int u, int p) 
{
    lt[u] = ++ttime;
    s[u] = s[p] + a[u];
    for (int v : g[u]) 
    {
        if (v == p) continue;
        dfs(v, u);
    }
    rt[u] = ttime;
}

int main() 
{
    ios_base::sync_with_stdio(0);
    cin >> n >> q;
    for (int i=1; i<=n; ++i) 
        cin >> a[i];

    for (int i=1, u, v; i<n; ++i) 
    {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);  

    for (int i=1; i<=n; ++i) 
        it.update(1,1,n,lt[i],lt[i],s[i]);

    for (int i=1,k,u,v; i<=q ;++i) 
    {
        cin >> k >> u;
        if(k == 1)  
        {
            cin >> v;
            it.update(1, 1, n, lt[u], rt[u], v - a[u]);
            a[u] = v;
        }
        else 
        {
            cout << it.get(1, 1, n, lt[u]) << '\n';
        }
    }
    return 0;
}