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

bool check(const vector<int>& a, int k, int to, int d) {
  for (int i = 0; i < k; i++) {
    int last = 1;
    for (int j = i; j < (int)a.size(); j += k) {
      if (a[j] - last > d) {
        return false;
      }
      last = a[j];
    }
    if (to - last > d) {
      return false;
    }
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m, k, d;
  scanf("%d%d%d%d", &n, &m, &k, &d);
  vector<int> c(m);
  for (int &x : c) {
    scanf("%d", &x);
  }
  vector<int> a(k);
  for (int &x : a) {
    scanf("%d", &x);
  }

  sort(a.begin(), a.end());

  int l = 0, r = m + 1;
  while (r - l > 1) {
    int cnt = (l + r) / 2;

    if (check(a, cnt, n, d)) {
      l = cnt;
    } else {
      r = cnt;
    }
  }

  sort(c.begin(), c.end());
  if (l) {
    ll ans = 0;
    for (int i = 0; i < m - l; i++) {
      ans += c[i];
    }
    printf("%lld\n", ans);
  } else {
    ll ans = 0;
    for (int i = 1; i < m; i++) {
      ans += c[i];
    }
    a.insert(a.begin(), 1);
    a.push_back(n);
    for (int i = 1; i < (int)a.size(); i++) {
      if (a[i] - a[i-1] > d) {
        ans += c[0];
      }
    }
    printf("%lld\n", ans);
  }

  return 0;
}
