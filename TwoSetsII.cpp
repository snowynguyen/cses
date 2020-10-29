#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw (int a, int b) 
{
    if (b == 0) 
        return 1;
    int c= pw (a, b/  2);
    c = c * 1LL * c % mod;
    if (b % 2 == 1) 
        c = c * 1LL * a % mod;
    return c;
}

int main() 
{
    int n; cin >> n;
    int sum = n * (n + 1) / 2;
    if ( sum % 2 == 1) 
    {
        cout << 0; return 0;
    }

    vector<int> F(sum / 2 + 1, 0);
    F[0] = 1;
    for (int i=1; i<=n; ++i) 
    {
        for (int j=sum / 2; j>=i; --j) 
        {
            F[j] += F[j-i];
            F[j] %= mod;
        }
    }
    cout << F[sum / 2] * 1LL * pw(2, mod - 2) % mod;
    return 0;
}