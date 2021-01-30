#include <bits/stdc++.h>
using namespace std;

int f[501][501];

int F(int x, int y) 
{\
    if (x == y) 
        return 0;
    if (f[x][y]) 
        return f[x][y];
    f[x][y] = 1e9;
    for (int k = 1; k + k <= y; ++k) 
        f[x][y] = min(f[x][y], F(x, k) + F(x, y - k) + 1);
    for (int k = 1; k + k <= x; ++k) 
        f[x][y] = min(f[x][y], F(k, y) + F(x - k, y) + 1);
    return f[x][y];
}

int main() 
{
    int x, y; cin >> x >> y;
    cout << F(x, y);
}