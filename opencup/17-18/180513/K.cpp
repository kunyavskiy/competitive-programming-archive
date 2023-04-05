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

static const int BUBEN = 20;

const double alpha = 0.0755605;
double magic(double a, double b) {
  return ((a + b) - sqrt(a * a - (1 + 3 * alpha) * a * b + b * b)) / (6 * (1 + alpha));
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n = 1000001;
  vector<ll> d(n);

  for (int i = 3; i < n; i++) {
//    int bestX = 0;
    int xx =(int)magic(i, i);
    for (int x = max(0, xx - BUBEN); x * 2 < i && x < xx + BUBEN; x++) {
      ll s = (i - 2ll * x) * (i - 2ll * x) * x + 4 * d[x];
      if (s > d[i]) {
        d[i] = s;
//        bestX = x;
      }
    }
//    cout << d[i] << ",";
//    double a =  d[i] / (1.0 * i * i * i);
//    cout << a << " " << (2 - sqrt(1 - 3 * a)) / (6 * (1 + a)) << " " << 1.0 * bestX / i << "\n";
//    assert(abs(bestX - (int)magic(i, i)) <= 20);
  }
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    ll best = 0;
    int xx =(int)magic(a, b);
    for (int x = max(0, xx - BUBEN); x * 2 < min(a, b) && x <= xx + BUBEN; x++) {
      ll s = (a - 2ll * x) * (b - 2ll * x) * x + 4 * d[x];
      best = max(best, s);
    }
    cout << best << "\n";
  }

  return 0;
}
