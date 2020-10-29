#include <bits/stdc++.h>
using namespace std;

const int N = 2501;

long long f[N];
int n, m;
struct TEdge 
{
    int u, v, w;
}e[N * 4];

const long long ooo = 1e18;
long long ans = -ooo;

bool ford_bellman() 
{
    bool ret = 0;
    for (int i=0; i<m; ++i) 
    {
        if (f[e[i].u] + e[i].w > f[e[i].v]) 
        {
            if (f[e[i].v] == n) 
                ret = 1;
            f[e[i].v] = f[e[i].u] + e[i].w;
        }
    }
    ans = max(ans, f[n]);
    return ret;
}

int main() 
{
    cin >> n >> m;
    for (int i=0; i<m; ++i )
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
       // e[i+m] = e[i];
      //  swap(e[i+m].u, e[i+m].v);
    }
 //   m += m;

    for (int i=1; i<=n; ++i)  
    //for (int j=1; j<=n; ++j) 
        f[i] = -ooo;

    f[1] = 0;
    for (int z = n + n; z>=0; --z) 
    {
        ford_bellman();
    }
    if (ford_bellman()) 
    {
        cout << -1;
    }
    else 
    {
        cout << ans;
    }
}