#include <bits/stdc++.h>
using namespace std;

int main() 
{
    int n, x;  cin >> n >> x;
    const int mod = 1e9  + 7;
    vector<int> F(x + 1, 0);
    F[0] = 1;
    for (int i=1,v; i<=n; ++i) 
    {
        cin >> v;
        for (int j=v; j<=x; ++j) 
        {
            F[j] = (F[j] + F[j - v]) % mod;
        }
    }

    cout << F[x];
}