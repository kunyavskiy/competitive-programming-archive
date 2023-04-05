#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time : %.3lf s.\n", (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct request {
  int l, r, id;
};

vector<ll> res;

void go(vector<pair<int, int>> a, vector<request> q) {
  int n = a.size();
  int m = q.size();
  vector<vector<int>> rr(n);
  for (int i = 0; i < m; i++) {
    rr[q[i].r].push_back(i);
  }
  vector<pair<int, ll>> st = {{-1, 0}};
  vector<ll> ps(n + 1);
  for (int i = 0; i < n; i++) {
    ps[i + 1] = ps[i] + a[i].first;
  }
  for (int i = 0; i < n; i++) {
    while (st.back().first != -1 && a[i] > a[st.back().first]) {
      st.pop_back();
    }
    st.push_back({i, st.back().second + 1ll * a[i].first * (i - st.back().first)});
    for (int j : rr[i]) {
      int l1 = 0;
      int r1 = st.size();
      while (r1 > l1 + 1) {
        int m1 = (l1 + r1) / 2;
        if (st[m1].first < q[j].l) l1 = m1; else r1 = m1;
      }
      ll s1 = st.back().second - st[r1].second;
      ll s2 = ps[i + 1] - ps[st[r1].first + 1];
      res[q[j].id] += s1 - s2;
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, q;
  scanf("%d%d", &n, &q);
  vector<pair<int, int>> h(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &h[i].first);
    h[i].second = i;
  }
  vector<request> r(q);
  for (int i = 0; i < q; i++) {
    scanf("%d%d", &r[i].l, &r[i].r);
    r[i].l--;
    r[i].r--;
    r[i].id = i;
  }
  res.resize(q);
  go(h, r);
  reverse(h.begin(), h.end());
  for (auto &p : r) {
    int ll = n - 1 - p.r;
    int rr = n - 1 - p.l;
    p.l = ll;
    p.r = rr;
  }
  go(h, r);
  for (int i = 0; i < q; i++) {
    cout << res[i] << "\n";
  }

  return 0;
}
