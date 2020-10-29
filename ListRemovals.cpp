#include <bits/stdc++.h>
using namespace std;

const int N = 200002;
int a[N], n, p[N];

struct TSegmentTree 
{
    int f[N*4];

    void init(int id = 1, int l = 1, int r = n) 
    {
        if (l == r) 
            f[id] = 1;
        else 
        {
            int m = (l + r)/ 2;
            init(id * 2, l, m);
            init(id*2+1, m+1, r);
            f[id] = f[id * 2] + f[id * 2 + 1];
        }
    }

    int walk(int id, int l, int r, int x) 
    {
        if (l == r) 
            return l;
        int m = (l + r) / 2;
        if (f[id * 2] < x) 
            return walk(id * 2 + 1, m + 1, r, x - f[id * 2]);
        else 
            return walk(id * 2, l, m, x);
    }

    void update (int id, int l, int r, int p, int det) 
    {
        if (r < p || p < l)
            return;
        if (l == r) 
            f[id] += det;
        else 
        {
            int m = (l + r) / 2;
            update (id * 2, l, m, p, det);
            update (id*2+1,m+1, r, p, det);
            f[id] = f[id * 2] + f[id * 2 +1];
        }
    }
} it;

int main() 
{
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> a[i];
    for (int i=1; i<=n; ++i) cin >> p[i];
    it.init();
    for (int i=1,u; i<=n; ++i) 
    {
        u = it.walk(1, 1, n, p[i]);
        cout << a[u] << " ";
        it.update(1, 1, n, u, -1);
    }

}