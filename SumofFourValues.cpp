#include <bits/stdc++.h>
using namespace std;

int n, x, a[1000];
#define pii pair<int , int>
#define lint long long

struct TPair 
{
    lint sum;
    int i, j;

    TPair () {}
    TPair (lint sum, int i, int j) : sum(sum), i(i), j(j) {}

    bool operator < (const TPair &h) const 
    {
        return sum < h.sum;
    }
};
vector<TPair> f;

int main() 
{
    cin >> n >> x;
    for (int i=0; i<n; ++i)
        cin >> a[i];
    for (int i=1; i<n; ++i)
    {
        for (int j=0; j<i; ++j) 
        {
            f.push_back({a[i] + a[j], j, i});
        }
    }
    sort (f.begin(), f.end());
    lint demand;
    TPair dummy;
    int lo, hi, k;
    vector<int> ans;
    for (int i=0; i<n; ++i) 
    for (int j=i+1; j<n; ++j) 
    {
        demand = (lint)x - a[i] - a[j];
        dummy = TPair(demand, 0, 0);
        lo = lower_bound(f.begin(), f.end(), dummy) - f.begin();
        hi = upper_bound(f.begin(), f.end(), dummy) - f.begin();
        for (k=lo; k<hi; ++k) 
        {
            if (f[k].i != i && f[k].i != j && f[k].j != i && f[k].j != j) 
            {
                ans = {i, j, f[k].i, f[k].j};
                sort(ans.begin(), ans.end());
                for (int ele:ans) cout << ele+1 << " ";
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE";
}