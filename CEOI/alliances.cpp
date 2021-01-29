#include <bits/stdc++.h>
using namespace std;

const int N = 72;
int m,n;
int s[N][N];
char r[N][N][3][3];
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const vector<int> MK[5] = {{0},{1,2,4,8},{3,6,9,12},{7,11,13,14},{15}};

int main() 
{
    cin >> m >> n;
    for (int i=1; i<=m; ++i) 
    {
        for (int j=1; j<=n; ++j) 
        {
            cin >> s[i][j];
        }
    }
    for (int it = m * n; it > 0; --it) 
    {
        for (int x=1, y, u,v, d, mask; x<=m; ++x) 
        {
            for (y =1 ; y<=n; ++y) 
            {
                if (s[x][y] == 0) continue;
                mask = 0;
                for (d=0; d<4; ++d) 
                {
                    u = x + dx[d];
                    v = y + dy[d];
                    if (1 <= u && u <= m && 1 <= v && v <= n) 
                    {
                        if (s[u][v] > 0) 
                        {
                            mask |= 1 << d;
                        }
                    }
                }
            }
        }
    }
}
