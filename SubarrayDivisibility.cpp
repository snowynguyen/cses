#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<int> p(n, 0);
    int pre = 0;
    long long ret = 0;
    p[0] = 1;
    for (int i=1; i<=n; ++i)
    {
        int x; cin >> x;
        pre = ((pre + x) % n + n) % n;
        ret += p[pre];
        p[pre]++;
    }
    cout << ret; 
}