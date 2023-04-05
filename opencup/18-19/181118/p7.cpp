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
#include <bits/stdc++.h>

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

struct Query {
  pair<int, int> start;
  vector<pair<int, int>> monster;
  vector<pair<int, int>> weapon;
};

vector<string> fast(vector<pair<int, int>> a, vector<Query> q) {
  int n = a.size();
  sort(a.begin(), a.end());

  auto getId = [&](const pair<int, int> &o) {
    return (int)(lower_bound(a.begin(), a.end(), o) - a.begin());
  };

  vector<pair<int, int>> edges;
  for (int i = 0; i < n; i++) {
    for (int dx = 0; dx < 2; dx++) {
      int dy = 1 - dx;
      auto nw = make_pair(a[i].first + dx, a[i].second + dy);
      int j = getId(nw);
      if (j < n && a[j] == nw) {
        edges.push_back({i, j});
      }
    }
  }

  vector<vector<int>> del(n);

  int m = q.size();
  for (int i = 0; i < m; i++) {
    for (auto o : q[i].weapon) {
      int id = getId(o);
      assert(id < n && a[id] == o);
      del[id].push_back(i);
    }
  }

  int N = 1;
  while (N < m) N <<= 1;

  vector<vector<int>> t(N * 2);
  auto add = [&](int L, int R, int eid) {
    L += N;
    R += N;
    while (L <= R) {
      if (L & 1) t[L].push_back(eid);
      if (!(R & 1)) t[R].push_back(eid);
      L = (L + 1) >> 1;
      R = (R - 1) >> 1;
    }
  };

  auto Merge = [&](vector<int> &a, vector<int> b) {
    vector<int> c(a.size() + b.size());
    merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    a = c;
  };

  for (int i = 0; i < (int)edges.size(); i++) {
    vector<int> cdel(2);
    cdel[0] = -1;
    cdel[1] = m;
    Merge(cdel, del[edges[i].first]);
    Merge(cdel, del[edges[i].second]);
    cdel.resize(unique(cdel.begin(), cdel.end()) - cdel.begin());

    for (int j = 1; j < (int)cdel.size(); j++) {
      if (cdel[j - 1] + 1 < cdel[j]) {
        add(cdel[j - 1] + 1, cdel[j] - 1, i);
      }
    }
  }

  vector<pair<int*, int>> st;
  auto upd = [&](int *a, int b) {
    st.push_back(make_pair(a, *a));
    *a = b;
  };

  vector<int> p(n), cnt(n, 1);
  iota(p.begin(), p.end(), 0);

  function<int(int)> get = [&](int v) {
    if (v == p[v]) return v;
    upd(&p[v], get(p[v]));
    return p[v];
  };
  auto uni = [&](int u, int v) {
    u = get(u);
    v = get(v);
    if (u == v) return;
    if (cnt[u] < cnt[v]) swap(u, v);
    upd(&p[v], u);
    upd(&cnt[u], cnt[u] + cnt[v]);
  };

  vector<string> ans(m);
  function<void(int, int, int)> dfs = [&](int v, int tl, int tr) {
    int was = st.size();
    for (auto eid : t[v]) {
      uni(edges[eid].first, edges[eid].second);
    }
    if (tl == tr) {
      if (tl < m) {
        int v0 = get(getId(q[tl].start));
        bool fail = 0;
        for (auto o : q[tl].monster) {
          int vi = get(getId(o));
          if (v0 == vi) fail = 1;
        }
        ans[tl] = fail ? "fail" : "ok";
      }
    } else {
      int tm = (tl + tr) >> 1;
      dfs(v * 2, tl, tm);
      dfs(v * 2 + 1, tm + 1, tr);
    }
    while ((int)st.size() > was) {
      *st.back().first = st.back().second;
      st.pop_back();
    }
  };
  dfs(1, 0, N - 1);
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("p7.in", "r", stdin);
  //freopen("p7.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second);

    int q;
    scanf("%d", &q);
    vector<Query> b(q);
    for (int i = 0; i < q; i++) {
      int m, w;
      scanf("%d%d", &m, &w);
      b[i].monster.resize(m);
      b[i].weapon.resize(w);
      scanf("%d%d", &b[i].start.first, &b[i].start.second);
      for (int j = 0; j < m; j++) {
        scanf("%d%d", &b[i].monster[j].first, &b[i].monster[j].second);
      }
      for (int j = 0; j < w; j++) {
        scanf("%d%d", &b[i].weapon[j].first, &b[i].weapon[j].second);
      }
    }

    auto ans = fast(a, b);
    for (string s : ans) printf("%s\n", s.c_str());
  }

  return 0;
}
