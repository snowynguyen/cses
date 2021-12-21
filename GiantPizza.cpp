#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m;
vector<int> CC[N];

struct TG 
{
    vector<int> g[N];

    void addEdge (int u, int v) 
    {
        g[u].push_back(v);
    }

    int com[N], cid, nid, num[N], low[N];
    bool onStack[N];
    vector<int> stk;

    void dfs(int u) 
    {
        num[u] = low[u] = ++nid;
        onStack[u] = true;
        stk.push_back(u);
        for(int v : g[u]) 
        {
            if (!num[v]) 
                dfs(v);
            if (onStack[v]) 
                low[u] = min(low[u], low[v]);
        }
        if (num[u] == low[u]) 
        {
            ++cid;
            while (stk.back() != u) 
            {
                onStack[stk.back()] = false;
                com[stk.back()] = cid;
                CC[cid].push_back(stk.back());
                stk.pop_back(); 
            }
            onStack[u] = false;
            stk.pop_back();
            CC[cid].push_back(u);
            com[u] = cid;
        }
    }

    void tarjan() 
    {
        for (int i=2; i<=2 * n + 1; ++i) 
        {
            if (num[i] == 0) 
            {
                dfs(i);
            }
        }
    }
}G;


void enter() 
{
    cin >> m >> n;
    
    
    char c, d;int e, f;

    for (int i=1; i<=m; ++i) 
    {
        cin >> c >> e >> d >> f;
        if (c == '+' && d == '+') 
        {
            G.addEdge(e * 2, f * 2 + 1);
            G.addEdge(f * 2, e * 2 + 1);
        }
        else if (c == '+' && d == '-') 
        {
            G.addEdge(e * 2, f * 2);
            G.addEdge(f * 2 + 1, e * 2 + 1);
        }
        else if (c == '-' && d == '+') 
        {
            G.addEdge(e * 2 + 1, f * 2 + 1);
            G.addEdge(f * 2, e * 2);
        }
        else if (c == '-' && d == '-') 
        {
            G.addEdge(e * 2 + 1, f * 2);
            G.addEdge(f * 2 + 1, e * 2);
        }
    }
}
vector<int> Hrev[N];
vector<int> H[N];
char assignment[N];
int visited[N];

void solve() 
{
    G.tarjan();
    for (int i=1; i<=n; ++i)
        assignment[i] = '*';
    for (int i=1; i<=n; ++i) 
    {
        if (G.com[i * 2] == G.com[i * 2 + 1]) 
        {
            cout << "IMPOSSIBLE";
            return;
        }
    }

    for (int i=2; i<= n * 2 + 1; ++i) 
    {
        for (int j : G.g[i]) 
        {
            if (G.com[i] != G.com[j])
                H[G.com[i]].push_back(G.com[j]);
        }
    }
    vector<int> degOut(G.cid + 1, 0);
    queue<int> qc;
    for (int i=1; i<= G.cid; ++i) 
    {
        sort (H[i].begin(), H[i].end());
        H[i].resize(unique(H[i].begin(), H[i].end()) - H[i].begin());
        for (int j : H[i]) 
        {
            degOut[i]++;
            Hrev[j].push_back(i);
        }
    }
    for (int i=1; i<=G.cid; ++i) 
    {
        if (degOut[i] == 0) 
            qc.push(i);
    }

    queue<int> qu;

    while (qc.size()) 
    {
        int u = qc.front();
        qc.pop();

        for (int v : Hrev[u]) 
        {
            degOut[v]--;
            if (degOut[v] == 0) 
                qc.push(v);
        }

        if (visited[CC[u][0]]) 
            continue;
        
        for (int x : CC[u]) 
        {
            qu.push(x);
        }
        while (qu.size())
        {
            int x = qu.front(); qu.pop();
            if (x % 2 == 0) 
                assignment[x / 2] = '-';
            else 
                assignment[x / 2] = '+';
            visited[x] = visited[x ^ 1] = 1;
            for (int y : G.g[x]) 
            {
                if (!visited[y]) 
                {
                    qu.push(y);
                }
            }
        }
    }
    for (int i=1; i<=n; ++i) 
        cout << assignment[i] << ' ';
}

int main() 
{
    ios_base::sync_with_stdio(0);
    enter();
    solve();
}