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

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {

    ll ans = 0;
    vector<int> a(n);
    vector<int> b(m);

    const ll COEF = 1000 * 1000 * 1000;

    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      ans += a[i] * COEF;
    }
    for (int i = 0; i < m; i++) {
      scanf("%d", &b[i]);
      ans += b[i];
    }

    int maxa = *max_element(a.begin(), a.end());
    int maxb = *max_element(b.begin(), b.end());

    int maxal = -1, maxar = -1;
    for (int i = 0; i < n; i++) {
      if (a[i] == maxa) {
        maxal = i;
        break;
      }
    }

    for (int i = n - 1; i >= 0; i--) {
      if (a[i] == maxa) {
        maxar = i;
        break;
      }
    }

    ans += maxa * COEF * (m - 1);

    ans += maxal * b[0];
    ans += (n - maxar - 1) * b[m - 1];
    ans += maxb * (maxar - maxal);

    printf("%lld\n", ans);
  }

  return 0;
}
