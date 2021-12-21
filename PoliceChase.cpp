#include <bits/stdc++.h>
using namespace std;

int n, m;
const int N = 5002;

struct TEdge
{
    int v, rev, flow, cap;

    void add (int w) 
    {
        flow += w;
    }
};

struct TF
{
    vector<TEdge> g[N];

    void addEdge (int u, int v) 
    {
        g[u].push_back({v, (int)g[v].size(), 0, 1});
        g[v].push_back({u, (int)g[u].size() - 1, 0, 1});
    }

    vector<int > level;

    bool bfs() 
    {
        level.assign(n + 1, 0);
        queue<int> q;
        q.push(1);
        level[1] = 1;
        while (q.size()) 
        {
            int u = q.front(); q.pop();
            for (auto v : g[u]) 
            {
                if (v.flow < v.cap) 
                {
                    if (level[v.v] == 0) 
                    {
                        level[v.v] = level[u] + 1;
                        q.push(v.v);
                    }
                }
            }
        }
        return level[n];
    }

    vector<int> nt;

    int dfs(int u, int flow) 
    {
        if ( u == n) 
            return flow;

        int total = 0;
        
        for (int &j = nt[u]; j < g[u].size(); ++j)
        {
            auto &v = g[u][j];
            if (level[v.v] ==level[u] + 1) 
            {
                if (v.flow < v.cap) 
                {
                    int over = dfs(v.v, min(flow, v.cap - v.flow));
                    if (over) 
                    {
                        v.add(over);
                        total += over;
                    }
                    if (v.flow == v.cap) 
                    {
                        return total;
                    }
                }
            }
        }
        return total;
    }

    void dinic( )
    {
        int ret = 0;
        while (bfs()) 
        {
            nt.assign(n+1, 0);
            int a = 0;
            do 
            {
                a = dfs(1, N);
                ret += a;
            }while (a);
        }

        cout << ret;
        for (int i=1; i<=n; ++i) 
        {
            for (auto j : g[i])
            {
                if (level[i] > 0 && level[j.v] == 0) 
                {
                    cout << "\n" << i << " " << j.v;
                }
            }
        }
        cout << endl;
    }
}G ;

int main() 
{
    cin >> n >> m;
    for (int i=1,u,v; i<=m; ++i) 
    {
        cin >> u >> v;
        G.addEdge(u, v);      
    }
    G.dinic();
}