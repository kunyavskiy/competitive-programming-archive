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

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y)                                                              \
  cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z)                                                           \
  cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y   \
       << ", " << z << ")\n"
#define dbv(a)                                                                 \
  cerr << #a << " = ";                                                         \
  for (auto xxxx : a)                                                          \
    cerr << xxxx << " ";                                                       \
  cerr << endl

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


using int128 = __int128_t;

int128 ans[31][31][31][31 * 31];
int last[31][31][31][31*31];
int last_id;
int n;
int invp[31];

int128 get(int pos, int ins, int outs, int rem_sum, int outs_fixed) {
  rem_sum -= ins + outs + outs_fixed;
  if (ins < 0 || outs < 0 || rem_sum < 0) return 0;
  auto& res = ans[pos][ins][outs][rem_sum];
  if (last[pos][ins][outs][rem_sum] == last_id) return res;
  last[pos][ins][outs][rem_sum] = last_id;
  res = 0;
  if (pos == n) {
    if (ins == 0 && outs == 0 && rem_sum == 0) return res = 1;
    return res = 0;
  }
  if (invp[pos] == -1) {
    res += ins * outs * get(pos + 1, ins - 1, outs - 1, rem_sum, outs_fixed);
    res += (ins + outs + 1) * get(pos + 1, ins, outs, rem_sum, outs_fixed);
    res += get(pos + 1, ins + 1, outs + 1, rem_sum, outs_fixed);
  } else {
    res += ins * get(pos + 1, ins - 1, outs, rem_sum, outs_fixed - 1);
    res += get(pos + 1, ins, outs + 1, rem_sum, outs_fixed - 1);
  }
  assert(res >= 0);
  return res;
}

int main() {
  #ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int m;
  string ks;
  int128 k = 0;
  cin >> n >> m >> ks;
  for (char c : ks) {
    k = 10 * k + c - '0';
  }

  memset(ans, -1, sizeof(ans));

  vector<int> res(n, 0);
  k--;

  for (int i = 0; i < n; i++) {
    for (int& c = res[i];; c++) {
      assert(c < n);
      set used(res.begin(), res.begin() + i + 1);
      if ((int)used.size() != i + 1) continue;
      memset(invp, -1, sizeof(invp));
      int ins = 0;
      int outs = 0;
      for (int j = 0; j <= i; j++) {
        invp[res[j]] = j;
        if (res[j] > i) outs++;
        if (!used.contains(j)) ins++;
      }
      last_id++;
      auto r = get(i + 1, ins, 0, m, outs);
      eprintf("%d %d: ins=%d, outs=%d, r=%d, k = %d\n", i, c, ins, outs, (int)r, (int)k);
      if (k >= r) {
        k -= r;
      } else {
        m -= ins + outs;
        break;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    printf("%d ", res[i] + 1);
  }
  printf("\n");

  return 0;
}
