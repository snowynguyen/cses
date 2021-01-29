#include <bits/stdc++.h>
using namespace std;

const int N = 200002;
#define pii pair<int, int> 
#define lint long long 
int m, n;
pii R[N], C[N];

int b[2002][2002];
int ts[2002];

int sub1() 
{
    int nr = 0, nc = 0;

    for (int i=1; i<=n; ++i) 
        nc += C[i].second;

    for (int i=1; i<=m; ++i) 
    {
        for (int j = 1; j <= R[i].second; ++j) 
        {
            ++nr;
            for (int y = nc; y > nc - R[i].first; --y) 
            {
                b[nr][y] = 1;
                ts[y]++;
            }
        }
    }

    for (int i = n; i >= 1; --i) 
    {
        for (int z = 0; z < C[i].second; ++z) 
        {
            if (ts[nc] >= C[i].first) 
            {
                ts[nc-1] += ts[nc] - C[i].first;
                ts[nc] = C[i].first;
            }
            else
            {
                return 0;
            }
            
            --nc;
        }
    }
    return 1;
}

struct TPrefix 
{
    lint maxsize;
    map<lint , lint> M;

    void init(lint maxsize) 
    {
        M[0] = 0;
        this->maxsize = maxsize;
    }

    void update (lint l, lint r, lint x)  
    {
        M[l] += x;
        M[r + 1] -= x;
    }

    vector< lint>  I, P, PP, II;

    void build() 
    {
        I.reserve(n+m);
        PP.reserve(n+m);
        P.reserve(n+m);
        lint p = 0;
        for (auto x : M) 
        {
            I.push_back(x.first);
            p += x.second;
            P.push_back(p);
        }
        p = 0;
        lint lasti = 0;
        PP = {0};
        II = {0};
        for (int i=1; i< I .size() - 1; ++i) 
        {
            II.push_back(I[i + 1] - 1);
            PP.push_back(PP[i-1] + P[i] * (I[i + 1] - I[i]));
        }
    }    

    lint get(lint p) 
    {
        int i = upper_bound(II.begin(), II.end(), p) - II.begin() - 1;
        lint r = PP[i] + (p - II[i]) * P[i+1];
        return r;
    }

    lint get(lint l, lint r) 
    {
        return get(r) - get(l - 1);
    }
}helper;

int sub2() 
{
    long long nc = 0 , nr = 0 ;
    for (int i=1; i<=n; ++i) 
        nc += C[i].second;
    helper.init(nc);
    for (int i=1; i<=m; ++i) 
    {
        helper.update(nc - R[i].first + 1, nc, R[i].second);
    }
    helper.build();
    lint rem = 0;
    for (int i=n; i>=1; --i) 
    {
        rem += helper.get(nc - C[i].second + 1, nc);
        nc -= C[i].second;
        if (rem < C[i].first * C[i].second) 
        {
            return 0;
        }
        else 
        {
            rem -= C[i].first * C[i].second;
        }
    }
    return 1;
}

int main() 
{
    ios_base::sync_with_stdio(0);
    cin >> m;
    for (int i=1; i<=m; ++i) 
    {
        cin >> R[i].first >> R[i].second;
    }
    cin >> n;
    for (int i=1; i<=n; ++i) 
    {
        cin >> C[i].first >> C[i].second;
    }
    sort (R + 1, R + 1 + m);
    sort (C + 1, C + 1 + n);
    cout << sub2();
}