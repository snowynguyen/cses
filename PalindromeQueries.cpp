#include <bits/stdc++.h>
using namespace std;

const int K = 3, BASE = 131;
const int mod[K] = {1000696969, 987654319, 987654323};

int Pow (int a, int b, int mod) 
{
    if (b == 0) 
        return 1;
    long long c = Pow(a, b/2, mod);
    c = c * c % mod;
    if (b % 2 == 1) 
        c = c * a % mod;
    return c;
}

struct TSegTree
{
    int n, mod;
    string s;
    vector<int> f, pw, inv;
    TSegTree (string s, int mod) : mod(mod)
    {
        n = s.size();
        this->s = " " + s;
        f.assign(n * 4, 0);     
        pw.assign(n + 1, 0);
        inv.assign(n + 1, 0);
        pw[0] = 1;
        for (int i=1; i<=n; ++i) 
        {
            pw[i] = (long long) pw[i-1] * BASE % mod;
        }
        inv[n] = Pow(pw[n], mod-2, mod);
        for (int i=n-1; i>=0; --i) 
        {
            inv[i] = (long long) inv[i+1] * BASE % mod;
        }  
        init(1, 1, n);
    }

    void init(int id, int l, int r) 
    {
        if (l == r) 
            f[id] = (long long)(s[l]-'a'+1) * pw[l] % mod;
        else 
        {
            int m = (l + r) / 2;
            init(id * 2, l, m);
            init(id * 2 + 1, m + 1, r);
            f[id] = (f[id * 2] + f[id * 2 + 1]) % mod;
        }
    }

    int get (int id, int l, int r, int u, int v)
    {
        if (r < u || v < l) 
            return 0;
        if (u <= l && r <= v) 
            return f[id];
        int m = (l + r) / 2;
        return (get(id * 2, l, m, u, v) + get(id * 2 + 1, m + 1,r, u, v)) % mod;
    }

    void update (int id, int l, int r, int p, char x)
    {
        if (r < p || p < l) 
            return;
        if (l == r) 
        {
            f[id] = (long long)(x-'a'+1) * pw[p] % mod;
        }
        else 
        {
            int m = (l + r) / 2;
            update (id * 2, l, m, p, x);
            update (id*2+1, m + 1, r, p, x);
            f[id] = (f[id * 2] + f[id * 2 + 1]) % mod;
        }
    }

    int GET (int u, int v) 
    {
        int ret = get(1, 1, n, u, v);
        ret = (long long)ret * inv[u] % mod;
        return ret;
    }

    void UPDATE (int p, int x) 
    {
        update (1, 1, n, p, x);
    }
};

int main() 
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    string s; cin >> s;
    string t = s;
    reverse(t.begin(), t.end());
    TSegTree hs(s, mod[0]), ht(t, mod[0]);

    int ty, u, v; char c;
    int t1, t2;
    for (int i=1; i<=m; ++i) 
    {
        cin >> ty >> u;
        if (ty == 1) 
        {
            cin >> c;
            hs.UPDATE(u, c);
            ht.UPDATE(n+1-u, c);
        }
        else 
        {
            cin >> v;
            t1 = hs.GET(u, v);
            t2 = ht.GET(n+1-v, n+1-u);
            if (t1 == t2) 
            {
                cout << "YES\n";
            }
            else 
            {
                cout << "NO\n";
            }
        }
    }
}