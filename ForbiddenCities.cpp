#include<bits/stdc++.h>
using namespace std;

/** @return the block-cut tree of a graph 
 * Let c_1,...,c_p be the cut points of the graph;
 * Let b_1,...,b_q be the blocks of the graph.
 * The block-cut tree consists of p+q nodes.
 *    g = { {1,2},
            {0,2},
            {0,1,3},
            {4,5,2},
            {3,5},
            {3,4}};
    auto blockcut = biconnected_components(g, iscutpoint, roots);
    // cuts     = {2, 3}
    // blocks   = {{3, 5, 4}, {2, 3}, {0, 2, 1}}
    // 0-3, 0-4, 1-2, 1-3
*/
vector<vector<int>> biconnected_components(const vector<vector<int>> &g,   
                                            vector<bool> &is_cutpoint, vector<int> &id) {
	int n = (int)g.size();
	vector<vector<int>> comps;
	vector<int> stk;
	vector<int> num(n);
	vector<int> low(n);
	is_cutpoint.resize(n);

	// Finds the biconnected components
	function<void(int, int, int &)> dfs = [&](int node, int parent, int &timer) {
		num[node] = low[node] = ++timer;
		stk.push_back(node);
		for (int child : g[node]) {
			if (child == parent) { continue; }
			if (num[child]) {
				low[node] = min(low[node], num[child]);
			} else {
				dfs(child, node, timer);
				low[node] = min(low[node], low[child]);
				if (low[child] >= num[node]) {
					is_cutpoint[node] = (num[node] > 1 || num[child] > 2);
					comps.push_back({node});
					while (comps.back().back() != child) {
						comps.back().push_back(stk.back());
						stk.pop_back();
					}
				}
			}
		}
	};

	int timer = 0;
	dfs(0, -1, timer);
	id.assign(n, -1);

	// Build the block-cut tree
	function<vector<vector<int>>()> build_tree = [&]() {
		vector<vector<int>> t(1);
		int node_id = 0;
		for (int node = 0; node < n; node++) {
			if (is_cutpoint[node]) {
				id[node] = node_id++;
				t.push_back({});
			}
		}

		for (auto &comp : comps) {
			int node = node_id++;
			t.push_back({});
			for (int u : comp)
				if (!is_cutpoint[u]) {
					id[u] = node;
				} else {
					t[node].push_back(id[u]);
					t[id[u]].push_back(node);
				}
		}
		return t;
	};

	return build_tree();
}

struct LCA{
    int K, n;
    vector<vector<int> > p;
    vector<int> d, f;

    LCA(const vector<vector<int > > &g) {
        n = g.size();
        K = log2(n) + 1;
        p.assign(K, vector<int> (n, 0));
        d.assign(n, -1);
        f.assign(n, 0);

        dfs(0, -1, g);

        for (int k=1; k<K; ++k) {
            for (int u=0; u<n; ++u) {
                p[k][u] = p[k-1][p[k-1][u]];
            }
        }
    }

    void dfs(int u, int par, const vector<vector<int > > &g)  {
        for (auto v : g[u]) {
            if (v == par) 
                continue;
            if (d[v] != -1)
                continue;
            d[v] = d[u] + 1;
            p[0][v] = u;
            f[v] = f[u] + v;
            dfs(v, u, g);
        }
    }

    int lca(int u, int v) {
        if (d[u] > d[v]) {
            swap(u, v);
        }
        for (int k=K-1; k>=0; --k) {
            if (d[v] - (1 << k) >= d[u]) {
                v = p[k][v];
            }
        }
        if (u == v) 
            return u;
        for (int k=K-1; k>=0; --k) {
            if (p[k][u] != p[k][v]) {
                u = p[k][u];
                v = p[k][v];
            }
        }
        return p[0][u];
    }

    bool isOnPath(int ancestor, int descendant, int target) {
        // ancestor IS ASSUMED to be the ancestor of the descendant
        if (target == descendant || target == ancestor)
            return true; 
        if (d[target] >= d[descendant] || d[target] <= d[ancestor]) 
            return false; 
        for (int k=K-1; k>=0; --k) {
            if (d[descendant] - (1 << k) >= d[target]) {
                descendant = p[k][descendant];
            }
        }
        return descendant == target;
    }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	int n, m, q; cin >> n >> m >> q;;
    vector<vector<int > > g(n);
    for (int i=0; i<m; ++i) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<bool> is_cut;
    vector<int> ids;
    auto block_cut_tree = biconnected_components(g, is_cut, ids);
    LCA lca(block_cut_tree);

    for (int i=0; i<q; ++i) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--; c--;
        bool ans;
        if (a == c || b == c) 
            ans = false;
        else if (!is_cut[c]) 
            ans = true;
        else {
            int ta = ids[a], tb = ids[b], tc = ids[c];
            int tlca = lca.lca(ta, tb);
            ans = !(lca.isOnPath(tlca, ta, tc) || lca.isOnPath(tlca, tb, tc));
        } 
        if (ans) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}