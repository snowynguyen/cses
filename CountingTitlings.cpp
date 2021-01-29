#include <bits/stdc++.h>
using namespace std;

const int N = 10, M = 1002, mod = 1000000007;
int f[M][1 << N];
int n, m;

bool done[M][1 << N];

int F(int i, int mask) 
{
    if (i > m) 
        return mask == 0;
    if (done[i][mask]) 
        return f[i][mask];
    
    for (int j=1; j<n; ++j) 
    {
        if ((!(mask & (1 << (j- 1)))) && (!(mask & (1 << j)))) 
        {
            f[i][mask] = (f[i][mask] + F(i, mask | (1 << j) | (1 << (j - 1))));
        }
    }

    f[i][mask] += F(i + 1, ((1 << n) - 1) ^ mask);
    done[i][mask] = true;
    return f[i][mask];
}

int main()
{
    cin >> n >> m;
    cout << F(1, 0);
}