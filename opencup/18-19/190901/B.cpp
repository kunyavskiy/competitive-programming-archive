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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

vector<int> gen_cnts(int m, const vector<int> &pred, const vector<int> &cycle, int l, int r) {
  vector<int> ans(m);
  while (l < (int)pred.size() && l < r) {
    ans[pred[l++]]++;
  }
  l -= pred.size();
  r -= pred.size();
  while (l < r && l % cycle.size()) {
    ans[cycle[(l++) % cycle.size()]]++;
  }
  while (l < r && r % cycle.size()) {
    ans[cycle[(--r) % cycle.size()]]++;
  }
  int cycles = (r - l) / cycle.size();
  for (int x : cycle) {
    ans[x] += cycles;
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int test_id = 1; test_id <= t; test_id++) {
    printf("Case #%d: ", test_id);
    int m, a, c, x, l1, r1, l2, r2;
    scanf("%d%d%d%d%d%d%d%d", &m, &a, &c, &x, &l1, &r1, &l2, &r2);

    vector<int> pred, cycle;
    {
      vector<int> used(m, -1);
      while (used[x] == -1) {
        used[x] = pred.size();
        pred.push_back(x);
        x = (x * 1LL * a + c) % m;
      }
      cycle.insert(cycle.begin(), pred.begin() + used[x], pred.end());
      pred.erase(pred.begin() + used[x], pred.end());
    }

    vector<int> lf = gen_cnts(m, pred, cycle, l1, r1 + 1);
    vector<ll> lf_sum = vector<ll>(m + 1);
    ll ans = 0;
    for (int i = 0; i < m; i++) {
      ans += lf[i] * 1LL * i * (r2 - l2 + 1);
      lf_sum[i + 1] = lf_sum[i] + lf[i];
    }
    vector<int> rg = gen_cnts(m, pred, cycle, l2, r2 + 1);


    for (int i = 1; i <= m; i++) {
      if (!rg[i - 1]) continue;
      ll cur = 0;
      for (int j = 0; j <= m / i; j++) {
        cur += (lf_sum[min((j + 1) * i, m)] - lf_sum[j * i]) * 1LL * j;
      }
      ans -= cur * rg[i - 1] * i;
    }

    printf("%lld\n", ans);
  }

  return 0;
}
