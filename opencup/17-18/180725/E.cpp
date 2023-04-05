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

const int MAXN = 300000;

const int MOD = 1000000007;

int sum(int a, int b) {
  if ((a += b) >= MOD) a -= MOD;
  return a;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

const ll INF = 1LL << 60;

struct min_with_cnt {
  ll weight;
  int cnt;

  min_with_cnt() {
    weight = -INF;
    cnt = 0;
  }

  min_with_cnt(ll weight, int cnt) : weight(weight), cnt(cnt) {
  }
};


min_with_cnt operator*(const min_with_cnt& a, const min_with_cnt& b) {
  if (a.weight == b.weight) {
    return {a.weight, sum(a.cnt, b.cnt)};
  }
  if (a.weight > b.weight) {
    return a;
  }
  return b;
}

min_with_cnt operator+(const min_with_cnt& a, const min_with_cnt& b) {
  return {a.weight + b.weight, mul(a.cnt, b.cnt)};
}


struct edge {
  min_with_cnt w[4];
  edge() {
    for (int i = 0; i < 4; i++) {
      w[i] = min_with_cnt();
    }
  }

  void print() const {
    for (int i = 0; i < 4; i++) {
      eprintf("(%lld,%d)", w[i].weight, w[i].cnt);
    }
  }
};

edge merge_series(const edge& a, const edge& b) {
  edge res;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((i & 1) && (j & 1)) {
        continue;
      }
      int to = ((i & 2) >> 1) | (j & 2);
      res.w[to] = res.w[to] * (a.w[i] + b.w[j]);
    }
  }
  /*
  a.print();
  eprintf("+");
  b.print();
  eprintf(" = ");
  res.print();
  eprintf("\n");
  */
  return res;
}

edge merge_parallel(const edge& a, const edge& b) {
  edge res;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i & j) {
        continue;
      }
      int to = i | j;
      res.w[to] = res.w[to] * (a.w[i] + b.w[j]);
    }
  }
  /*
  a.print();
  eprintf("*");
  b.print();
  eprintf(" = ");
  res.print();
  eprintf("\n");
  */

  return res;
}

map<int, edge> es[MAXN];

void adde(map<int, edge>& x, int to, const edge& e) {
  auto it = x.find(to);
  if (it == x.end()) {
    x[to] = e;
  } else {
    it->second = merge_parallel(it->second, e);
  }
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    es[i].clear();
  }
  for (int i = 0; i < m; i++) {
    int a, b, w;
    scanf("%d%d%d", &a, &b, &w);
    --a; --b;
    edge x;
    x.w[0] = {0, 1};
    x.w[3] = {w, 1};
    adde(es[a], b, x);
    adde(es[b], a, x);
  }

  queue<int> q;
  vector<bool> inq(n);
  for (int i = 0; i < n; i++) {
    if (es[i].size() == 2) {
      q.push(i);
      inq[i] = true;
    }
  }

  for (int i = 0; i < n - 2; i++) {
    assert(!q.empty());
    int x = q.front();
    q.pop();
    assert(es[x].size() == 2);
    int u = es[x].begin()->first;
    int v = es[x].rbegin()->first;

//    eprintf("series u=%d v=%d\n", u, v);
    edge eu = es[x].begin()->second;
    edge ev = es[x].rbegin()->second;

    es[u].erase(x);
    es[x].erase(u);
    es[x].erase(v);
    es[v].erase(x);

    adde(es[u], v, merge_series(eu, ev));
    adde(es[v], u, merge_series(ev, eu));

    if (es[u].size() == 2 && !inq[u]) {
      q.push(u);
      inq[u] = true;
    }
    if (es[v].size() == 2 && !inq[v]) {
      q.push(v);
      inq[v] = true;
    }
  }

  int a, b;
  a = b = -1;
  for (int i = 0; i < n; i++) {
    assert(es[i].size() <= 2);
    if (es[i].size() == 1) {
      if (a == -1) a = i;
      else if (b == -1) b = i;
      else assert(0);
    }
  }

  min_with_cnt ans;

//  eprintf("a = %d, b = %d\n", a, b);

  edge r = es[a].begin()->second;
//  r.print();
//  eprintf("\n");
  for (int i = 0; i < 4; i++) {
    ans = ans * r.w[i];
  }
  printf("%lld %d\n", ans.weight, ans.cnt);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();

  return 0;
}
