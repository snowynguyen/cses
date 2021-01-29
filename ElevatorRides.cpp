#include <bits/stdc++.h>
using namespace std;

#define pii pair<int ,int > 
const int N = 20;
pii f[1 << N];
int n;
int w, a[N];

int main() 
{
    cin >> n >> w;
    for (int i=0; i<n; ++i) 
        cin >> a[i];

    for (int i=1; i< (1 << n); ++i) 
        f[i] = {n, 0};

    for (int z, i = 0, k; i < (1 << n) - 1; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            if (!(i & (1 << j))) 
            {
                k = i | (1 << j);
                z = f[i].second + a[j];
                if (z > w) 
                {
                    f[k] = min(f[k], make_pair(f[i].first + 1, a[j]));
                }
                else 
                {
                    f[k] = min(f[k], make_pair(f[i].first, z));
                }
            }
        }
    }
    int r = f[(1 << n) - 1].first + (!!(f[(1 << n) - 1]).second);
    cout << r;
}
