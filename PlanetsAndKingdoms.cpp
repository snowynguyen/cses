#include <bits/stdc++.h>
using namespace std;

const int N = 100002;
vector<int> g[N];
int n, m;

void enter() 
{
    cin >> n >> m;
    for (int i=1; i<=m; ++i) 
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }
}

int num[N], low[N], nid;
vector<int> stk;
bool onStack[N];
int com[N], cid;

void dfs(int u)
{
    stk.push_back(u); onStack[u] = true;
    num[u] = ++nid;
    low[u] = num[u];
    for (int v : g[u]) 
    {
        if (num[v] == 0) 
            dfs(v);
        if (onStack[v]) 
            low[u] = min(low[u], low[v]);
    }
    if (onStack[u] && num[u] == low[u]) 
    {
        ++cid;
        while (stk.back() != u) 
        {
            com[stk.back()] = cid;
            onStack[stk.back()] = false;
            stk.pop_back();
        }
        com[u] = cid;
        onStack[u] = false;
        stk.pop_back();
    }
}

void solve() 
{
    nid = 0;

    for (int i=1; i<=n; ++i) 
    {
        if (!num[i]) 
        {
            dfs(i);
        }
    }

    cout << cid << endl;
    for (int i=1; i<=n; ++i) 
        cout << com[i] << ' ';
}

int main() 
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    enter();
    solve();
}