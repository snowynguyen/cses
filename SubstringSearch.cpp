#include<bits/stdc++.h>
using namespace std;

struct SA {
    string s;
    vector<int> p;
    int n;

    SA (string s) : s(s) {
        s = s + "$";
        n = s.size();
        p.resize(n); 
    
        for (int i=0; i<n; ++i) 
            p[i] = i;
        
        sort (p.begin(), p.end(), [&] (int a, int b) {
            return s[a] < s[b];
        });
        vector<int> rank(n, 0);
        for (int i=0; i<n; ++i) {
            rank[i] = lower_bound(p.begin(), p.end(), i, [&] (int a, int b) {
                return s[a] < s[b];
            }) - p.begin();
        }
        
        vector<int> rank_new(n), p_new(n), cnt(n);
        for (int k=1; k<n; k*=2) {
            for (int i = 0; i < n; i++) {
                p_new[i] = p[i] - k;
                if (p_new[i] < 0) p_new[i] += n;
            }
            cnt.assign(n, 0); rank_new.assign(n, 0);
            for (int i = 0; i < n; i++)
                cnt[rank[p_new[i]]]++;
            for (int i = 1; i < n; i++)
                cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--)
                p[--cnt[rank[p_new[i]]]] = p_new[i];
            rank_new[p[0]] = 0;
            int classes = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {rank[p[i]], rank[(p[i] + k) % n]};
                pair<int, int> prev = {rank[p[i-1]], rank[(p[i-1] + k) % n]};
                if (cur != prev)
                    ++classes;
                rank_new[p[i]] = classes;
            }
            rank.swap(rank_new);
        }
    }
};

// Input "ppppplppp" -> Output "9 5 8 4 7 3 6 2 1 0"
// "ababba" -> "6 5 0 2 4 1 3" 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    SA sa(s);
    int n; 
    cin >> n;
    while(n--) {
        string t; cin >> t;
        int L = 0, R = sa.n - 1; 
        bool found = false;

        while (L <= R) {
            int M = (L + R) / 2;

            int comp = 0, si, ti;
            for ( si=sa.p[M], ti=0; si<s.size() && ti<t.size(); si++,ti++) {
                if (s[si] != t[ti]) {
                    comp = (s[si] < t[ti]) ? -1 : 1;
                    break;
                }
            }
            if (comp == 0) {
                if (ti == t.size()) {
                    found = true;
                    break;
                } else {
                    comp = -1;
                }
            }
            
            if (comp == -1) {
                L = M + 1;
            } else {
                R = M - 1;
            }
        }

        cout << ((found) ? "Yes" : "No") << endl;
    }
}