#include "bits/stdc++.h"
using namespace std;

#define ld long double

struct TLine {
    ld a, b;

    TLine(ld a, ld b) : a(a), b(b) {}

    ld eval(ld x) const {
        return a * x + b;
    }

    ld intersect(const TLine &rhs) const {
        return (rhs.b - b) / (a - rhs.a);
    }

    bool operator < (const TLine& rhs) const {
        return a < rhs.a;
    }
};

int n, x;
const int N = 100002;
int s[N], f[N];

void input() {
    cin >> n >> x;
    for (int i=1; i<=n; ++i) {
        cin >> s[i];
    }
    for (int i=1; i<=n; ++i) {
        cin >> f[i];
    }
}

ld solve() {
    deque<TLine> lines;
    TLine init_line = TLine(x, 0);
    lines.push_back(init_line);
    ld y = 0;
    deque<ld> intersection_points;
    int j = 0;
    for (int i=1; i<=n; ++i) {
        while (j + 1 < intersection_points.size() && intersection_points[j] <= s[i]) 
            ++j;
        y = lines[j].eval(s[i]);
        TLine new_line = TLine(f[i], y);

        while (lines.size() >= 2) {
            ld xn = lines[lines.size() - 1].intersect(lines[lines.size() - 2]);
            ld xm = lines[lines.size() - 1].intersect(new_line);
            if (xm <= xn) {
                lines.pop_back();
                intersection_points.pop_back();
            } else {
                break;
            }
        }
        
        ld last_intersection = lines.back().intersect(new_line);
        intersection_points.push_back(last_intersection);
        lines.push_back(new_line);
    }
    return y;
}

int main(int argc, char* argv[]) 
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    auto res = solve();
    cout << res;
}