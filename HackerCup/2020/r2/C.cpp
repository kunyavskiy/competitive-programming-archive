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

void PreCalc() {
}

vector<int> read_gen(int n, int k, int d) {
  vector<int> data;
  data.resize(k);
  for (int &x : data) scanf("%d", &x);
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  while ((int)data.size() < n) {
    data.push_back((a * 1LL * data[data.size()- 2] + b * 1LL * data.back() + c) % d);
  }
  return data;
}

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


void solve() {
  int n, m, e, k;
  scanf("%d%d%d%d", &n, &m, &e, &k);
  auto x = read_gen(n, k, m);
  auto y = read_gen(n, k, m);
  auto eid = read_gen(e, k, n * m + n);
  auto w = read_gen(e, k, 1'000'000'000);

  vector<multiset<int>> up(n);
  vector<multiset<int>> dn(n);
  vector<pair<int, int>> rmv(n, {-1, -1});
  multiset<int> main;

  vector<int> cur_cost(n * m + n, 1);
  long long cur_total_cost = n * m + n;
  long long cur_total_removed = 0;
  long long main_removed = -1;
  for (int i = 0; i < n; i++) {
    main.insert(1);
  }

  auto disjoin_main = [&] {
    assert(main_removed == -1);
    main_removed = *main.rbegin();
    main.erase(--main.end());
    cur_total_removed += main_removed;
  };

  auto join_main = [&] {
    assert(main_removed != -1);
    cur_total_removed -= main_removed;
    main.insert(main_removed);
    main_removed = -1;
  };

  auto disjoin = [&](int id) {
    assert(rmv[id].first == -1);
    assert(!dn[id].empty());
    rmv[id].first = *dn[id].rbegin();
    dn[id].erase(--dn[id].end());
    if (!up[id].empty()) {
      rmv[id].second = *up[id].rbegin();
      up[id].erase(--up[id].end());
    }
    cur_total_removed += max(rmv[id].first, rmv[id].second);
    main.insert(min(rmv[id].first, rmv[id].second));
  };

  auto join = [&](int id) {
    assert(rmv[id].first != -1);
    main.erase(main.find(min(rmv[id].first, rmv[id].second)));
    cur_total_removed -= max(rmv[id].first, rmv[id].second);
    if (rmv[id].second != -1) {
      up[id].insert(rmv[id].second);
      rmv[id].second = -1;
    }
    dn[id].insert(rmv[id].first);
    rmv[id].first = -1;
  };

  for (int i = 0; i < n; i++) {
    if (x[i] > y[i]) {
      swap(x[i], y[i]);
    }
    for (int j = x[i]; j < y[i]; j++) {
      up[i].insert(1);
    }
    for (int j = y[i]; j < m; j++) {
      dn[i].insert(1);
    }
    for (int j = 0; j < x[i]; j++) {
      dn[i].insert(1);
    }
    disjoin(i);
  }
  disjoin_main();

  int ans = 1;
  for (int q = 0; q < e; q++) {
    int id = eid[q];
    int nw = w[q];
    cur_total_cost -= cur_cost[id];
    join_main();
    if (id >= n * m) {
      main.erase(main.find(cur_cost[id]));
      main.insert(nw);
    } else {
      int cycle = id / m;
      int in_cycle = id % m;
      join(cycle);

      if (x[cycle] <= in_cycle && in_cycle < y[cycle]) {
        up[cycle].erase(up[cycle].find(cur_cost[id]));
        up[cycle].insert(nw);
      } else {
        dn[cycle].erase(dn[cycle].find(cur_cost[id]));
        dn[cycle].insert(nw);
      }

      disjoin(cycle);
    }
    disjoin_main();
    cur_cost[id] = nw;
    cur_total_cost += nw;
    ll cur_ans = cur_total_cost - cur_total_removed;
//    eprintf("%lld\n", cur_ans);
    ans = mul(ans, cur_ans % MOD);
  }
//  eprintf("\n");

  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
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
