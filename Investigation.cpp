#include <bits/stdc++.h>
using namespace std;

const int N = 100002,  MOD = 1e9+7;
#define lint long long 
const lint INF = 1e18;

struct TNode {
    long long w;
    int u;

    TNode(int u, lint w): u(u), w(w) {}
    bool operator < (const TNode &h) const {
        return w > h.w;
    }
};

struct TEdge {
    int v,w;
};

int n, m;
vector<vector<TEdge > > g;

void enter() {
    cin >> n >> m;
    g.assign(n + 1, vector<TEdge> ());
    for (int u,v,w,i=0;i<m; ++i) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
}

vector<lint> solve() {
    priority_queue<TNode> q;
    vector<lint> f(n + 1, INF);
    q.emplace(1, 0);
    f[1] = 0;
    lint w;

    vector<int> min_e (n + 1, MOD), max_e(n + 1, -1);
    vector<int> cnt_paths(n + 1, 0);
    vector<bool> visited(n + 1, false);
    min_e[1] = max_e[1] = 0; cnt_paths[1] = 1;
    while (!q.empty()) {
        auto u = q.top();
        q.pop();
        if (visited[u.u]) continue;
        visited[u.u] = true;
        for (auto v : g[u.u]) {
            if (visited[v.v]) 
                continue;
            w = f[u.u] + v.w;
            if (w < f[v.v]) {
                f[v.v] = w;
                min_e[v.v] = 1+min_e[u.u];
                max_e[v.v] = 1+max_e[u.u];
                cnt_paths[v.v] = cnt_paths[u.u];
                q.emplace(v.v, w);
            } else if (w  == f[v.v]) {
                cnt_paths[v.v] = (cnt_paths[v.v] + cnt_paths[u.u]) % MOD;
                min_e[v.v] = min(min_e[v.v], min_e[u.u] + 1);
                max_e[v.v] = max(max_e[v.v], max_e[u.u] + 1);
            }
        }
    }
    return {f[n], cnt_paths[n], min_e[n], max_e[n]};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    enter();
    auto s = solve();
    cout << s[0] << " " << s[1] << " " << s[2] << " " << s[3] << endl;
    return 0;
}