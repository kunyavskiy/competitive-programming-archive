#include <cassert>
#include <fstream>
#include <iostream>
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

char buf[123456];

struct item {
  int ll, lr, rl, rr;
};

item merge(const item& a, const item &b, int out) {
  item res;
  res.ll = min(a.ll + b.ll, a.lr + b.rl);
  res.lr = min(a.ll + b.lr, a.lr + b.rr);
  res.rl = min(a.rl + b.ll, a.rr + b.rl);
  res.rr = min(a.rl + b.lr, a.rr + b.rr);
  res.ll = min(res.ll, res.lr + out);
  res.lr = min(res.lr, res.ll + out);
  res.rl = min(res.rl, res.rr + out);
  res.rr = min(res.rr, res.rl + out);
  return res;
}

const int INF = 1e9;

void solve() {
  int n, q;
  scanf("%d%d", &n, &q);
  scanf("%s", buf);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%*d");
    }
  }
  n /= 2;

  const int LOG = 18;

  vector<int> map(2 * n);
  vector<vector<int>> childs(n + 1);
  vector<int> h(n + 1);
  vector<vector<int>> up(LOG, vector<int>(n + 1));
  vector<vector<item>> ups(LOG, vector<item>(n + 1));
  vector<int> v;
  v.push_back(0);
  int pt = 1;
  for (int i = 0; i < 2 * n; i++) {
    if (buf[i] == '(') {
      up[0][pt] = v.back();
      h[pt] = h[v.back()] + 1;
      childs[v.back()].push_back(pt);
      v.push_back(pt);
      map[i] = pt;
      pt++;
    } else {
      map[i] = v.back();
      v.pop_back();
    }
  }

  n++;
  for (int i = 1; i < n; i++) {
    int p = up[0][i];
    int pos = lower_bound(childs[p].begin(), childs[p].end(), i) - childs[p].begin();
    ups[0][i] = merge({0, 1, 1, 0}, {2 * pos + 1, INF, INF, 2 * (int) childs[p].size() - 2 * pos - 1}, p == 0 ? INF : 1);
  }
  for (int i = 1; i < LOG; i++) {
    for (int j = 0; j < n; j++) {
      int pp = up[i - 1][j];
      up[i][j] = up[i - 1][pp];
      ups[i][j] = merge(ups[i - 1][j], ups[i - 1][pp], up[i][j] == 0 ? INF : 1);
    }
  }

  ll res = 0;
  vector<int> s(q);
  vector<int> t(q);
  for (int qq = 0; qq < q; qq++) {
    scanf("%d", &s[qq]); --s[qq];
  }
  for (int qq = 0; qq < q; qq++) {
    scanf("%d", &t[qq]); --t[qq];
  }

  for (int qq = 0; qq < q; qq++) {
    int x = s[qq], y = t[qq];
    if (x == y) {
      continue;
    }
    if (map[x] == map[y]) {
      res += 1;
      continue;
    }
    int vx = map[x];
    int vy = map[y];
    item lf{0, 1, 1, 0}, rg{0, 1, 1, 0};
    for (int i = LOG - 1; i >= 0; i--) {
      if (h[vx] - (1 << i) >= h[vy]) {
        lf = merge(lf, ups[i][vx], 1);
        vx = up[i][vx];
      }
    }
    for (int i = LOG - 1; i >= 0; i--) {
      if (h[vy] - (1 << i) >= h[vx]) {
        rg = merge(ups[i][vy], rg, 1);
        vy = up[i][vy];
      }
    }
    item ans;
    if (vx == vy) {
      ans = merge(lf, rg, 1);
    } else {
      for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][vx] != up[i][vy]) {
          lf = merge(lf, ups[i][vx], 1);
          vx = up[i][vx];
          rg = merge(ups[i][vy], rg, 1);
          vy = up[i][vy];
        }
      }
      assert(vx != vy);
      assert(up[0][vx] == up[0][vy]);
      int p = up[0][vx];
      int posx = lower_bound(childs[p].begin(), childs[p].end(), vx) - childs[p].begin();
      int posy = lower_bound(childs[p].begin(), childs[p].end(), vy) - childs[p].begin();
      item inner;
      auto path = [](int a, int b, int c) {
        return min(abs(a - b), c - abs(a - b));
      };
      inner.ll = path(2 * posx, 2 * posy, p == 0 ? INF : 2 * childs[p].size() + 2);
      inner.lr = path(2 * posx, 2 * posy + 1, p == 0 ? INF : 2 * childs[p].size() + 2);
      inner.rl = path(2 * posx + 1, 2 * posy, p == 0 ? INF : 2 * childs[p].size() + 2);
      inner.rr = path(2 * posx + 1, 2 * posy + 1, p == 0 ? INF : 2 * childs[p].size() + 2);
      ans = merge(merge(lf, inner, INF), rg, 1);
    }
    int cur = 0;
    if (buf[x] == '(' && buf[y] == '(') {
      cur = ans.ll;
    }
    if (buf[x] == '(' && buf[y] == ')') {
      cur = ans.lr;
    }
    if (buf[x] == ')' && buf[y] == '(') {
      cur = ans.rl;
    }
    if (buf[x] == ')' && buf[y] == ')') {
      cur = ans.rr;
    }
//    eprintf("%d\n", cur);
    res += cur;
  }
  printf("%lld\n", res);
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
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
