#include <bits/stdc++.h>
using namespace std;

const int N = 200001;

int n, q, A[N];
struct TQ
{
    int t, a, b;
} Q[N];

void enter() 
{
    cin >> n >> q;
    for (int i=1; i<=n; ++i) 
        cin >> A[i];
    for (int i=1; i<=q; ++i) 
        cin >> Q[i].t >> Q[i].a >> Q[i].b;
}

#define lint long long 
lint p[N];

struct TSegmentTree 
{
    lint unit[N * 4];
    lint x2[N*4];
    lint x[N*4];

    void build (int id, int l, int r) 
    {
        if (l == r) 
            unit[id] = p[l];
        else 
        {
            int m = (l + r) / 2;
            build(id * 2, l, m);
            build(id* 2 + 1, m + 1, r);
        }
    }

    void updateUV (int id, int l, int r, int u, int v) 
    {
        if (r < u || v < l)
            return;
        if (u <= l && r <= v) 
        {
            x2[id]++;
            x[id] += 3 - 2 * u;
            unit[id] += (1 - u) *(lint) (2 - u) / 2;
        }
        else 
        {
            int m = (l + r) / 2;
            updateUV(id * 2, l, m, u, v);
            updateUV(id * 2 + 1, m+1, r, u, v);
        }
    } 

    void updateR (int id, int l, int r, int u, lint w) 
    {
        if (r < u) 
            return;
        if (u <= l) 
        {
            unit[id] += w;
        }
        else 
        {
            int m = (l + r) / 2;
            updateR(id * 2, l, m, u, w);
            updateR(id * 2 + 1, m + 1, r, u, w);
        }
    }

    lint get (int id, int l, int r, int p) 
    {
        if (r < p || p < l) 
            return 0;
        lint ret = unit[id] + (x2[id] * p * p + x[id] * p) / 2;
        if (l < r) 
        {
            int m =(l + r) / 2;
            ret += get(id * 2, l, m, p);
            ret += get(id * 2 + 1, m+1, r, p);
        }
        return ret;
    }
}it;

void solve() 
{
    for (int i=1; i<=n; ++i) 
        p[i] = p[i-1] + A[i];
    it.build(1, 1, n);
    lint pl,pr;
    for (int i=1; i<=q; ++i) 
    {
        if (Q[i].t == 1) 
        {
            it.updateUV(1, 1, n, Q[i].a, Q[i].b);
            if (Q[i].b < n) 
                it.updateR(1, 1, n, Q[i].b+1, (lint)(Q[i].b - Q[i].a + 1) * (Q[i].b - Q[i].a + 2) / 2);
        }
        else 
        {
            pr = it.get(1, 1, n, Q[i].b);
            pl = 0;
            if (Q[i].a > 1) 
                pl = it.get(1, 1, n, Q[i].a - 1);
            cout << pr - pl << '\n';  
        }
    }   
}

int main() 
{
    ios_base::sync_with_stdio(0);
    enter();
    solve();
}