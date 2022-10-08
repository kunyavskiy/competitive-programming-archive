#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

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

void solve() {
  int r, c;
  scanf("%d%d", &r, &c);
  vector<set<int>> h(r);
  vector<set<int>> v(c);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      h[i].insert(j);
      v[j].insert(i);
    }
  }
  vector<vector<int>> skill(r, vector<int>(c));
  ll tot = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      scanf("%d", &skill[i][j]);
      tot += skill[i][j];
    }
  }
  vector<vector<ll>> score(r, vector<ll>(c));
  set<tuple<ll, int, int>> s;
  auto prev = [](const set<int>& a, int pos) {
    auto it = a.lower_bound(pos);
    if (it == a.begin()) {
      return -1;
    }
    --it;
    return *it;
  };
  auto next = [](const set<int>& a, int pos) {
    auto it = a.lower_bound(pos);
    assert(it != a.end());
    ++it;
    if (it == a.end()) {
      return INT32_MAX;
    }
    return *it;
  };

  auto recalc = [&](int i, int j) {
    if (i < 0 || i >= r) return;
    if (j < 0 || j >= c) return;
    assert(skill[i][j] != -1);
    s.erase(make_tuple(score[i][j], i, j));
    int cnt = 0;
    ll &sc = score[i][j];
    sc = 0;
    {
      int ppos = prev(h[i], j);
      if (ppos >= 0) {
        cnt++;
        sc -= skill[i][ppos];
      }
      int npos = next(h[i], j);
      if (npos < c) {
        cnt++;
        sc -= skill[i][npos];
      }
    }

    {
      int ppos = prev(v[j], i);
      if (ppos >= 0) {
        cnt++;
        sc -= skill[ppos][j];
      }
      int npos = next(v[j], i);
      if (npos < r) {
        cnt++;
        sc -= skill[npos][j];
      }
    }

    sc += cnt * 1LL * skill[i][j];
    s.insert(make_tuple(score[i][j], i, j));
  };

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      recalc(i, j);
    }
  }

  auto kill = [&](int x, int y) {
    assert(skill[x][y] != -1);
    s.erase(make_tuple(score[x][y], x, y));
    int pr = prev(h[x], y);
    int nr = next(h[x], y);
    int pc = prev(v[y], x);
    int nc = next(v[y], x);
    tot -= skill[x][y];
    skill[x][y] = -1;
    h[x].erase(y);
    v[y].erase(x);
    recalc(x, pr);
    recalc(x, nr);
    recalc(pc, y);
    recalc(nc, y);
  };

  ll ans = 0;
  while (true) {
    ans += tot;
    vector<pair<int, int>> to_kill;
    while (!s.empty() && get<0>(*s.begin()) < 0) {
      to_kill.emplace_back(get<1>(*s.begin()), get<2>(*s.begin()));
      s.erase(s.begin());
    }
    if (to_kill.empty()) {
      break;
    }
    for (auto x : to_kill) {
      kill(x.first, x.second);
    }
  }

  printf("%lld\n", ans);

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
