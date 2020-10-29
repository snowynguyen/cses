#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, a[N];

struct TSegmentTree 
{
    int f[N * 4];

    void init(int id, int l, int r) 
    {
        if (l == r) 
            f[id] = a[l];
        else 
        {
            int m = (l + r ) / 2;
            init(id * 2, l, m);
            init(id * 2 + 1, m + 1, r);
            f[id] = max(f[id*2], f[id * 2 + 1]);
        }
    }

    void update (int id, int l, int r, int p, int delta) 
    {
        if (r < p || p < l) 
            return;
        if (l == r) 
            f[id] += delta;
        else 
        {
            int m = (l + r ) / 2;
            update (id * 2, l,m, p ,delta);
            update (id*2+1, m+1, r, p, delta);
            f[id] = max(f[id*2], f[id * 2+1]);
        } 
    }

    int walk(int id, int l, int r, int x) 
    {
        if (l == r) 
        {
            if (f[id] < x) 
                return 0;
            return l;
        }
        int m = ( l + r) / 2;
        if (f[id * 2] >= x) 
            return walk(id*2, l, m, x);
        return walk(id * 2+1, m+1, r, x);
    }
} st;

int main() 
{
    ios_base::sync_with_stdio(0);
    int m;
    cin >> n >> m;
    for (int i=1; i<=n; ++i) 
        cin >> a[i];
    st.init(1, 1, n);
    for (int u, v,  i=1; i<=m; ++i) 
    {
        cin >> u;
        v = st.walk(1, 1, n, u);
        if (v > 0) 
        {
            st.update(1, 1, n, v, -u);
        }
        cout << v << " ";
    }
}