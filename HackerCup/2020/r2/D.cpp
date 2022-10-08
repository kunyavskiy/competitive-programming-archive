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

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

struct linear {
  long long a, b;
  long long eval(long long x) const {
    return a * x + b;
  }
};

struct LiChao {
  struct node {
    int ls, rs;
    linear fun;
  };
  vector<node> nodes;

  static constexpr int max_val = 1LL << 20;

  void add(int node_id, linear fun, int l, int r) {
    int mid = (l + r) / 2;
    if (fun.eval(mid) < nodes[node_id].fun.eval(mid)) {
      swap(fun, nodes[node_id].fun);
    }
    if (r - l == 1) {
      return;
    }
    if (fun.a < nodes[node_id].fun.a) {
      if (nodes[node_id].rs == -1) {
        nodes.push_back({-1, -1, fun});
        nodes[node_id].rs = nodes.size() - 1;
      } else {
        add(nodes[node_id].rs, fun, mid, r);
      }
    }
    if (fun.a > nodes[node_id].fun.a) {
      if (nodes[node_id].ls == -1) {
        nodes.push_back({-1, -1, fun});
        nodes[node_id].ls = nodes.size() - 1;
      } else {
        add(nodes[node_id].ls, fun, l, mid);
      }
    }
  }

  long long find_min(int node_id, int val, int l, int r) {
    int mid = (l + r) / 2;
    if (val == mid) {
      return nodes[node_id].fun.eval(val);
    }
    long long res = nodes[node_id].fun.eval(val);
    if (val < mid && nodes[node_id].ls != -1) {
      res = min(res, find_min(nodes[node_id].ls, val, l, mid));
    }
    if (val > mid && nodes[node_id].rs != -1) {
      res = min(res, find_min(nodes[node_id].rs, val, mid, r));
    }
    return res;
  }

  long long find_min(int val) {
    assert(!nodes.empty());
    assert(0 <= val && val < max_val);
    return find_min(0, val, 0, max_val);
  }

  void add(const linear &fun) {
    if (nodes.empty()) {
      nodes.push_back({-1, -1, fun});
    } else {
      add(0, fun, 0, max_val);
    }
  }

  void merge(LiChao&& r) {
    if (nodes.size() < r.nodes.size()) {
      nodes.swap(r.nodes);
    }
    for (auto x : r.nodes) {
      add(x.fun);
    }
    r.nodes.clear();
  }

};

void PreCalc() {
}

vector<int> read_gen_i(int n, int k) {
  vector<int> data;
  data.resize(k);
  for (int &x : data) scanf("%d", &x);
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  while ((int)data.size() < n) {
    data.push_back((a * 1LL * data[data.size()- 2] + b * 1LL * data.back() + c) % data.size() + 1);
  }
  for (int &x : data) x--;
  return data;
}


vector<int> read_gen(int n, int k) {
  vector<int> data;
  data.resize(k);
  for (int &x : data) scanf("%d", &x);
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  while ((int)data.size() < n) {
    data.push_back((a * 1LL * data[data.size()- 2] + b * 1LL * data.back() + c) % d + 1);
  }
  return data;
}

vector<int> read_gen_d(int n, int k, int d) {
  vector<int> data;
  data.resize(k);
  for (int &x : data) scanf("%d", &x);
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  while ((int)data.size() < n) {
    data.push_back((a * 1LL * data[data.size()- 2] + b * 1LL * data.back() + c) % d + 1);
  }
  for (int &x : data) x--;
  return data;
}



void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  auto p = read_gen_i(n, k);
  auto l = read_gen(n, k);
  auto h = read_gen(n, k);
  auto x = read_gen_d(m, k, n);
  auto y = read_gen(m, k);

  vector<ll> totl(n);
  for (int i = 1; i < n; i++) {
    totl[i] = totl[p[i]] + l[i];
  }
  vector<vector<int>> qs(n);
  for (int i = 0; i < m; i++) {
    qs[x[i]].push_back(y[i]);
  }
  vector<LiChao> data(n);

  int ans = 1;

  for (int i = n - 1; i >= 0; i--) {
    long long ans_for_me;
    if (data[i].nodes.empty()) {
      ans_for_me = 0;
    } else {
      ans_for_me = -totl[i] * 1LL * h[i] + data[i].find_min(h[i]);
    }
    data[i].add({totl[i], ans_for_me});
    for (int y : qs[i]) {
      long long ans_for_q = -totl[i] * 1LL * y + data[i].find_min(y);
      assert(ans_for_q >= 0);
//      eprintf("ans for (%d, %d) = %lld\n", i + 1, y, ans_for_q);
      ans = mul(ans, (ans_for_q + 1) % MOD);
    }
    if (i) {
      data[p[i]].merge(std::move(data[i]));
    }
  }

  printf("%d\n", ans);

}


int main() {
#ifdef LOCAL
//  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
