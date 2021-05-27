#include <bits/stdc++.h>
using namespace std;

#define lint long long
#define pii pair<int, int> 
#define ld long double

string s, t;

const int K = 3, BASE = 307;
const int MOD[K] = {1000696969, 987654323, 1+(119<<23)};

struct THashItem
{
    int h[K];

    THashItem (int val = 0) {
        for (int i=0; i<K; ++i) 
            h[i] = val;
    }

    THashItem operator* (const int &h) const
    {
        THashItem ret = *this;
        for (int k = 0; k < K; ++k)
            ret.h[k] = (long long)(ret.h[k]) * h % MOD[k];
        return ret;
    }

    THashItem operator+ (const int &h) const
    {
        THashItem ret = *this;
        for (int k = 0; k < K; ++k) 
            ret.h[k] = (ret.h[k] + h) % MOD[k];
        return ret;
    }

    THashItem operator- (const THashItem &h) const
    {
        THashItem ret = *this;
        for (int k = 0; k < K; ++k) 
        {
            ret.h[k] = (this->h[k] - h.h[k]);
            if (ret.h[k] < 0) 
                ret.h[k] += MOD[k];
        }
        return ret;
    }

    THashItem operator* (const THashItem &h)const
    {
        THashItem ret;
        for (int k = 0; k < K; ++ k) 
            ret.h[k] = (long long)this->h[k] * h.h[k] % MOD[k];
        return ret;
    }

    bool operator== (const THashItem &h) const
    {
        for (int k = 0; k < K; ++k) 
            if ((this->h[k]) != h.h[k])
                return false;
        return true;
    }

    bool operator< (const THashItem &h) const
    {
        for (int k = 0; k < K; ++k)
            if ((this->h[k]) != h.h[k]) 
                return this->h[k] < h.h[k];
        return false;
    }
};

struct THashString
{
    vector<THashItem> pw, f;
    int n;

    THashString() {} 
    THashString(string s) 
    {
        n = s.size();
        s = " " + s;
        f.resize(n + 1);
        pw.resize(n + 1);
        f[0] = THashItem();
        pw[0] = THashItem(1);
        for (int i=1; i<=n; ++i)  
        {
            f[i] = f[i - 1] * BASE + s[i];
            pw[i] = pw[i - 1] * BASE;
        }
    }

    THashItem substr(int l, int r) 
    {
        return f[r] - (f[l - 1] * pw[r - l + 1]);
    }
};

const int maxn = 100002;
vector<THashItem> g[maxn];

void driver()
{
    string s; cin >> s;
    THashString H(s);
    int m; cin >> m;
    string t;
    THashString HT;
    THashItem ht;
    while(m--)
    {
        cin >> t;
        HT = THashString(t);
        ht = HT.substr(1, t.size());
        if (g[t.size()].size() == 0) 
        {
            for (int i=1,j=t.size(); j <= s.size(); ++i,++j) 
                g[t.size()].push_back(H.substr(i,j));
            sort (g[t.size()].begin(), g[t.size()].end());
        }
        cout << upper_bound(g[t.size()].begin(), g[t.size()].end(), ht) - lower_bound(g[t.size()].begin(), g[t.size()].end(), ht) << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    driver();
}