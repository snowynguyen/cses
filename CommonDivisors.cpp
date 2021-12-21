#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<int> a(n);
    const int MAXAI = 1000002;
    vector<int> cnt (MAXAI, 0);
    for (int &i : a) 
    {
        cin >> i;
        cnt[i]++;
    }

    for (int gcd = MAXAI - 1; gcd >= 1; --gcd) 
    {
        int cntMul = 0;
        for (int x = gcd; x < MAXAI; x += gcd) 
            cntMul += cnt[x];
        if (cntMul >= 2) 
        {
            cout << gcd;
            return 0;
        }
    }
}