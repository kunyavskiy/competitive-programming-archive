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

const ll MS[] = {100'002'345'678'000'061, 100'000'000'000'000'003};
const ll K = sizeof(MS) / sizeof(MS[0]);
#ifdef LOCAL
const ll MAX_ID = 11'000;
#else
const ll MAX_ID = 11'000'000;
#endif
ll fib[K][MAX_ID];

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
  for (int i = 0; i < K; i++) {
    assert(MS[i] <= std::numeric_limits<ll>::max() / 10);
  }
#endif
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int i = 0; i < K; i++) {
    fib[i][0] = 0;
    fib[i][1] = 1;
    for (int j = 2; j < MAX_ID; j++) {
      fib[i][j] = fib[i][j-1] + fib[i][j-2];
      if (fib[i][j] >= MS[i]) fib[i][j] -= MS[i];
    }
  }

  int n;
  cin >> n;
  vector<string> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end(), [](const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
  });

  map<array<ll, K>, int> s;
  double phi_log = log((1 + sqrt(5)) / 2);
  double sqrt5_log = log(sqrt(5));
  double ten_log = log(10);

  ll ans = 0;

  for (const auto& x : v) {
    array<ll, K> aa;
    for (int i = 0; i < K; i++) aa[i] = 0;
    for (char c : x) {
      for (int i = 0; i < K; i++) aa[i] = (aa[i] * 10 + c - '0') % MS[i];
    }
    int aprox = floor((ten_log * (x.size() - 1) + sqrt5_log) / phi_log) - 2;
    eprintf("%ld: %s, %d..%d\n", &x - &v[0], x.data(), aprox, aprox + 10);
    for (int fid = 0; fid < 10; fid++) {
      int index = aprox + fid;
      if (index < 0) continue;
      assert(aprox < MAX_ID);
      array<ll, K> needed;
      for (int i = 0; i < K; i++) {
        needed[i] = fib[i][index] - aa[i];
        if (needed[i] < 0) needed[i] += MS[i];
      }
      ans += s[needed];
      //if (s[needed] > 0)
      eprintf("%ld: %s, index = %d, needed[0] = %lld, found = %d\n", &x - &v[0], x.data(), index, needed[0], s[needed]);
    }
    s[aa]++;
  }

  cout << ans << endl;

  return 0;
}
