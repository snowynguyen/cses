#include <bits/stdc++.h>
using namespace std;

const int N = 100002, MOD = 1e9+7;
vector<vector < int > > g;
int n, m;
vector<int> f;

int F(int x) {
    if (x == n) 
        return 1;
    if (f[x] != -1)
        return f[x];
    f[x] = 0;
    for (int y : g[x]) {
        f[x] += F(y);
        if (f[x] >= MOD) {
            f[x] -= MOD;
        }
    }
    return f[x];
}

int solve() {
    f.assign(n + 1, -1);
    return F(1);
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    g.assign(n + 1, vector<int> ());
    for (int i=0,u,v; i < m; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
    }

    int s = solve();
    cout << s << endl;
    
}