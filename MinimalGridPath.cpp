#include<bits/stdc++.h>
using namespace std;
 
int n; 
vector<string> a;
const int N = 3003;
 
int vis[N][N];
 
int main() {
    cin >> n;
    a.assign(n + 1, "");
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
        a[i] =  " " + a[i];
    }
 
 
    vector<pair<int , int> > potential = {{1, 1}}, new_potential = {};
    string ans;
    ans.push_back(a[1][1]);
    for (int xy=2; xy<n+n; ++xy) {
 
        char bestC = 'Z';
        for (auto [x, y] : potential) {
            if (x < n) {
                if (a[x+1][y] < bestC) {
                    bestC = a[x+1][y];
                } 
            }
            if (y < n) {
                if (a[x][y+1] < bestC) {
                    bestC = a[x][y+1];
                }
            }
        }
        for (auto [x, y] : potential) {
            if (x < n) {
                if (a[x+1][y] == bestC) {
                    if (!vis[x+1][y]) 
                    {
                        vis[x+1][y] = true;
                        new_potential.push_back({x+1, y});
                    }
                }
            }
            if (y < n) {
                if (a[x][y+1] == bestC) {
                    if (vis[x][y+1]) continue;
                    vis[x][y+1] = true;
                    new_potential.push_back({x, y+1});
                }
            }
        }
        ans.push_back(bestC);
        swap(new_potential, potential);
        new_potential={};
    }
    cout << ans;
    return 0;
}