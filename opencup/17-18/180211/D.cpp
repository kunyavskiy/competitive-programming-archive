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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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
typedef pair<ll, int> pli;

bool can(const vector<ll> & a, const vector<ll> & t, ll MAXT) {
  int n = int(a.size());
  vector <ll> dp(n + 1);
  priority_queue<pli> s1;
  priority_queue<pli> s2;
  vector <bool> dels(n + 1, false);
  dp[n] = MAXT;
  s1.push({dp[n], n});
  s2.push({-(dp[n] - t[n - 1]), n});
  for (int i = n - 1; i >= 0; --i) {
    while (!s2.empty() && -s2.top().first < 2 * a[i]) {
      int num = s2.top().second;
      s2.pop();
      dels[num] = true;
    }
    if (s2.empty()) {
      return false;
    }
    while (dels[s1.top().second]) {
      s1.pop();
    }
    dp[i] = s1.top().first - 2 * a[i];
    if (i) {
      s1.push({dp[i], i});
      s2.push({-(dp[i] - t[i - 1]), i});
    }
  }
  return true;
}

bool solve() {
  int n;
  if (scanf("%d", &n) != 1) {
    return false;
  }

  vector <ll> t, a;
  for (int i = 0; i < n; ++i) {
    int tt, aa;
    scanf("%d%d", &tt, &aa);
    while (!a.empty() && a.back() <= aa) {
      t.pop_back();
      a.pop_back();
    }
    t.push_back(tt);
    a.push_back(aa);
  }

  ll L = -1;
  ll R = 2 * a[0] + t.back() + 1;
  while (L + 1 < R) {
    ll M = (L + R) / 2;
    if (can(a, t, M)) {
      R = M;
    } else {
      L = M;
    }
  }
  printf("%lld\n", R);

  return true;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  while(solve());

  return 0;
}
