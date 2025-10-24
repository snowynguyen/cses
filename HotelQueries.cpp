#include <bits/stdc++.h>
using namespace std;
const int INF = 1e8;

struct TSegmentTree {
    int n; vector<int> f;

    TSegmentTree(int n): n(n) {
        f.assign(4*n, 0);
    }

    void update(int id, int l, int r, int p, int delta) {
        if (r < p || p < l) return;
        if (l == r) {
            f[id] += delta; 
        } else {
            int m = (l + r) / 2; 
            update(id * 2, l, m, p, delta);
            update(id * 2 + 1, m + 1, r, p, delta); 
            f[id] = max(f[id * 2], f[id * 2 + 1]);
        }
    }

    void update(int p, int delta) {
        update(1, 1, n, p, delta);
    }

    int walkLeft(int id, int l, int r, int value) {
        if (l == r) {
            if (f[id] < value) 
                return INF;
            return l;
        }
        if (f[id] < value) 
            return INF; 
        int m = (l + r) / 2;
        if (f[id * 2] >= value) 
            return walkLeft(id * 2, l, m, value);
        return walkLeft(id * 2 + 1, m + 1, r, value);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin >> n >> m;
    TSegmentTree st(n);
    vector<int> a(n + 1);
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
        st.update(i, a[i]);
    }
    for (int i=1, x, y; i<=m; ++i) {
        cin >> x;
        y = st.walkLeft(1, 1, n, x);
        if (y == INF) 
            y = 0;
        cout << y << ' ';
        st.update(y, -x);
    }
}
