#include<bits/stdc++.h>
using namespace std;

int n; 
vector<string> a;

const int N = 3002;
int f[N][N];

vector<int> bucket[N];
vector<int> sted;

int main() {
    cin >> n;
    a.assign(n + 1, "");
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
        a[i] =  " " + a[i];
        bucket[i].reserve(n);
    }

    f[n][n] = 1;
    for (int max_bucket=0,xy = n+n-1; xy >=2; --xy) {

        sted.clear();
        for (int r,x=1,y=xy-1; x<=n && y>=1; x++,y--) {
            if (y > n) continue;

            r = N;
            if (x + 1 <= n) 
                r = f[x+1][y];
            if (y + 1 <= n) 
                r = min(r, f[x][y+1]);
            
            bucket[r].push_back(x);
            max_bucket = max(r, max_bucket);
        }
        for (int i=1; i<=max_bucket; ++i) {
            for (int e : bucket[i]) {
                sted.push_back(e);
            }
            bucket[i].clear();
        }

        for (int x : sted) {
            bucket[a[x][xy-x]].push_back(x);
        }
        sted.clear();
        for (int c='A'; c<='Z'; ++c) {
            for (int e: bucket[c]) {
                sted.push_back(e);
            }
            bucket[c].clear();
        }

        for (int i=0; i<sted.size(); ++i) {
            f[sted[i]][xy-sted[i]] = i + 1;
        }
    }

    int x=1,y=1;
    while (x!=n || y!=n) {
        cout << a[x][y];
        if (x==n) y++;
        else if (y==n) x++;
        else {
            if (f[x][y+1] < f[x+1][y])
                y++;
            else 
                x++;
        }
    }
    cout << a[n][n];
    return 0;
}