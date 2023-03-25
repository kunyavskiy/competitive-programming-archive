#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct edge {
    int from, to, id;
};

struct MaxSolver {
    vector<int> value;
    vector<int> count;
    int ans;

    MaxSolver(int vs, int total) : value(vs), count(total + 1), ans(0) {
        count[0] = vs;
    }

    void inc(int pos) {
        assert(0 <= pos && pos < (int)value.size());
        count.at(value[pos])--;
        value[pos]++;
        count.at(value[pos])++;
        ans = max(ans, value[pos]);
    }

    void dec(int pos) {
        assert(0 <= pos && pos < (int)value.size());
        count.at(value[pos])--;
        value[pos]--;
        count.at(value[pos])++;
        if (count[ans] == 0) ans--;
    }
};

struct Solver {
    vector<vector<int>> g;
    vector<vector<int>> colors;
    int cs, cstotal;

    explicit Solver(vector<vector<int>> colors_) : g(colors_.size()), colors(std::move(colors_)) {
        map<int, int> csm;
        cstotal = 0;
        for (auto &x : colors) {
            for (auto &y : x) {
                if (csm.find(y) == csm.end()) {
                    int s = csm.size();
                    csm[y] = s;
                }
                y = csm[y];
            }
            cstotal += x.size();
        }
        cs = csm.size();
    }

    void addEdge(int u, int v) {
        g[u].push_back(v);
    }

    vector<int> size;

    int dfs_sizes(int v) {
        size[v] = colors[v].size();
        for (int u : g[v]) {
            size[v] += dfs_sizes(u);
        }
        return size[v];
    }

    void move_to_in(int v, MaxSolver& in, MaxSolver& out, bool ignoreFirst) {
        for (int u : colors[v]) {
            in.inc(u);
            out.dec(u);
        }
        for (int i = ignoreFirst; i < (int)g[v].size(); i++) {
            move_to_in(g[v][i], in, out, false);
        }
    }

    void move_to_out(int v, MaxSolver& in, MaxSolver& out) {
        for (int u : colors[v]) {
            in.dec(u);
            out.inc(u);
        }
        for (int u : g[v]) {
            move_to_out(u, in, out);
        }
    }

    vector<int> solve() {
        size.resize(g.size());
        dfs_sizes(0);
        vector<int> lp(g.size(), -1);
        for (int i = 0; i < (int)g.size(); i++) {
            for (int &y : g[i]) {
                if (size[y] > size[g[i][0]]) {
                    swap(y, g[i][0]);
                }
            }
            if (!g[i].empty()) {
                lp[g[i][0]] = i;
            }
        }
        MaxSolver in(cs, cstotal), out(cs, cstotal);

        for (const auto &x : colors) {
            for (int y : x) {
                out.inc(y);
            }
        }

        vector<int> result(g.size());
        result[0] = out.ans;

        for (int i = 0; i < (int)g.size(); i++) {
            if (!g[i].empty()) continue;
            int v = i;
            while (true) {
                move_to_in(v, in, out, true);
                result[v] = out.ans + in.ans;
                if (lp[v] == -1) break;
                v = lp[v];
            }
            move_to_out(v, in, out);
        }


        return result;
    }
};


void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }
    vector<vector<int>> g(n);
    vector<vector<int>> id(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        id[u].push_back(i);
        g[v].push_back(u);
        id[v].push_back(i);
    }
    vector<int> used(n);

    int ans_all = 0;
    auto dfs0 = [&](auto dfs, int v, vector<int>& colors_used) -> void {
        colors_used.push_back(c[v]);
        used[v] = 1;
        for (int u: g[v]) {
            if (!used[u]) {
                dfs(dfs, u, colors_used);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            vector<int> colors_used;
            dfs0(dfs0, i, colors_used);
            sort(colors_used.begin(), colors_used.end());
            int ans_cur = 0;
            for (int s = 0; s < (int)colors_used.size();) {
                int j;
                for (j = s; j < (int)colors_used.size() && colors_used[j] == colors_used[s]; j++) {}
                ans_cur = max(ans_cur, j - s);
                s = j;
            }
            ans_all += ans_cur;
        }
    }

    eprintf("ans_all = %d\n", ans_all);

    vector<int> tin(n, -1);
    vector<int> tup(n);
    int timer = 0;
    vector<int> stack;

    auto dfs_bridges = [&](auto dfs, int v, int pid, vector<vector<int>>& comps, vector<edge>& bridges, vector<int> &not_bridges) -> void {
        stack.push_back(v);
        tin[v] = tup[v] = timer++;
        for (int nid = 0; nid < (int)g[v].size(); nid++) {
            int u = g[v][nid];
            int eid = id[v][nid];
            if (eid == pid) continue;
            if (tin[u] != -1) {
                if (tin[u] <= tin[v]) {
                    tup[v] = min(tup[v], tin[u]);
                    not_bridges.push_back(eid);
                }
                continue;
            }
            dfs(dfs, u, eid, comps, bridges, not_bridges);
            tup[v] = min(tup[u], tup[v]);
            if (tup[u] <= tin[v]) {
                not_bridges.push_back(eid);
            } else {
                bridges.push_back({v, u, eid});
                comps.emplace_back();
                while (true) {
                    int tt = stack.back();
                    stack.pop_back();
                    comps.back().push_back(tt);
                    if (tt == u) break;
                }
            }
        }
        if (pid == -1) {
            comps.push_back(stack);
            stack.clear();
        }
    };

    vector<int> ans(m);

    for (int i = 0; i < n; i++) {
        if (tin[i] == -1) {
            vector<vector<int>> comps;
            vector<edge> bridges;
            vector<int> not_bridges;
            dfs_bridges(dfs_bridges, i, -1, comps, bridges, not_bridges);
            for (int eid: not_bridges) {
                ans[eid] = ans_all;
            }
            reverse(comps.begin(), comps.end());
            vector<vector<int>> comps_colors(comps.size());
            map<int, int> cmp;
            for (int cid = 0; cid < (int)comps.size(); cid++) {
                for (int v : comps[cid]) {
                    cmp[v] = cid;
                    comps_colors[cid].push_back(c[v]);
                }
            }
            Solver s(comps_colors);
            vector<pair<int, int>> ans_id;
            for (auto [v, u, eid] : bridges) {
                ans_id.emplace_back(eid, cmp[u]);
                s.addEdge(cmp[v], cmp[u]);
            }
            vector<int> ans_local = s.solve();
            for (auto [eid, ansv] : ans_id) {
                ans[eid] = ans_all - ans_local[0] + ans_local[ansv];
            }
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d%c", ans[i], " \n"[i == m - 1]);
    }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
      solve();
  }

  return 0;
}
