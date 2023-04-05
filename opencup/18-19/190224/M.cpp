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

vector<int> calc_invs(const vector<int> &a) {
  vector<int> invs(a.size());
  vector<int> fenw(*max_element(a.begin(), a.end()) + 1, 0);

  auto add = [&](int n) {
    while (n < (int) fenw.size()) {
      fenw[n] += 1;
      n = n | (n + 1);
    }
  };

  auto get = [&](int n) {
    int ans = 0;
    while (n > -1) {
      ans += fenw[n];
      n = (n & (n + 1)) - 1;
    }
    return ans;
  };

  for (int i = 0; i < int(a.size()); ++i) {
    int x = a[i];
    invs[i] = i - get(x);
//    eprintf("invs[%d] = %d\n", i, invs[i]);
    add(x);
  }

  return invs;
}
#ifdef LOCAL
//#define GEN
#endif


bool solve() {
  int n;
  if (scanf("%d", &n) != 1 || !n) { return false; }
  eprintf("n = %d\n", n);
  vector<int> a(n);
#ifdef GEN
  for (int i = 0; i < n; ++i) {
    a[i] = i + 1;
  }
  random_shuffle(a.begin(), a.end());
#else
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
#endif

  vector<int> left = calc_invs(a);
  reverse(a.begin(), a.end());
  for (int i = 0; i < n; ++i) {
    a[i] = n + 1 - a[i];
  }
  vector<int> right = calc_invs(a);
  reverse(right.begin(), right.end());

  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    eprintf("%d %d\n", left[i], right[i]);
    ans += left[i];
  }

  int x = max_element(left.begin(), left.end()) - left.begin();
  int y = max_element(right.begin(), right.end()) - right.begin();
  ll ans2 = ans + 2 * n - 2 * left[x] - 2 * right[y];
//  assert(x != y || ans <= ans2);
  ans = min(ans, ans2);
  eprintf("ans = %lld\n", ans);
  printf("%lld\n", ans);
  return true;
}


int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif
  while(solve());
  return 0;
}
