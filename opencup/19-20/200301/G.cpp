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
#include <random>

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

int solve(int n, int p, int q, int s, vector<int> a, vector<int> b) {
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  reverse(a.begin(), a.end());

  const int INF = 1.01e9;
  int ll = -1, rr = INF;
  while (rr - ll > 1) {
    int M = (ll + rr) >> 1;

    int cnt = 0;
    int t = 0;
    while (t < p && a[t] + b[0] > s) t++;

    if (t < p) {
      multiset<int> d;
      int L = 0;
      while (L < q && b[L] < a[t] - M) L++;
      int R = L;
      while (R < q && b[R] <= a[t] + M && a[t] + b[R] <= s) R++;

      for (int i = L; i < R; i++) d.insert(b[i]);

      for (int i = t; i < p; i++) {
        while (L > 0 && b[L - 1] >= a[i] - M) {
          d.insert(b[--L]);
        }
        while (R < q && b[R] <= a[i] + M && a[i] + b[R] <= s) {
          d.insert(b[R++]);
        }
        while (!d.empty() && *d.rbegin() > a[i] + M) {
          d.erase(--d.end());
        }
        auto it = d.upper_bound(s - a[i]);
        if (it != d.begin()) {
          it--;
          cnt++;
          d.erase(it);
        }
      }
    }
    if (cnt >= n) rr = M;
    else ll = M;
  }
  if (rr == INF) rr = -1;
  return rr;
}

int slow(int n, int p, int q, int s, vector<int> a, vector<int> b) {
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  const int INF = 1.01e9;
  int ans = INF;
  vector<char> used(q);
  function<void(int, int, int)> rec = [&](int cur, int mx, int cnt) {
    if (cur == p) {
      if (cnt >= n) {
        ans = min(ans, mx);
      }
      return;
    }
    rec(cur + 1, mx, cnt);
    for (int i = 0; i < q; i++) {
      if (!used[i] && a[cur] + b[i] <= s) {
        used[i] = 1;
        rec(cur + 1, max(mx, abs(a[cur] - b[i])), cnt + 1);
        used[i] = 0;
      }
    }
  };
  rec(0, 0, 0);
  if (ans == INF) ans = -1;
  return ans;
}

void stress() {
  for (int it = 1122;; it++ ){
    mt19937 rnd(it);
    db(it);

    const int C = 100;
    const int N = 10;

    int p = rnd() % N + 1;
    int q = rnd() % N + 1;
    int n =rnd() % min(p, q) + 1;
    int s = rnd() % C + 1;
    vector<int> a(p), b(q);
    for (int i = 0; i < p; i++) {
      a[i] = rnd() % C + 1;
    }
    for (int i = 0; i < q; i++) {
      b[i] = rnd() % C + 1;
    }
    auto ans1 = solve(n, p, q, s, a,b);
    auto ans2 = slow(n, p, q, s, a,b);
    if (ans1 != ans2) {
      db2(ans1, ans2);
      db3(n, p, q);
      db(s);
      dbv(a);
      dbv(b);
      exit(0);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif
//  stress();

  int n, p, q, s;
  while (scanf("%d%d%d%d", &n, &p, &q, &s) == 4) {
    vector<int> a(p), b(q);
    for (int i = 0; i < p; i++) scanf("%d", &a[i]);
    for (int i = 0; i < q; i++) scanf("%d", &b[i]);
    printf("%d\n", solve(n, p, q, s, a, b));
  }

  return 0;
}
