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

double get_outer_ratio(int n) {
  double angle = M_PI / n;
  return 2.0 / sin(angle);
}

double get_inner_ratio(int n) {
  double angle = M_PI / n;
  return 2.0 / tan(angle);
}

double get_coef(int n, int m) {
  if (n >= 3e6 || m >= 3e6) {
    return 1.0;
  }

  double angle = 2 * M_PI / m;
  vector<double> v;
  double angle2 = 2 * M_PI / n;
  for (int i = 0; i < n; i++) {
    double x = angle2 * i;
    x -= (int)(x / angle) * angle;
    v.push_back(x);
  }
  sort(v.begin(), v.end());
  v.push_back(v[0] + angle);
  double max_diff = 0;
  for (int i = 1; i < (int)v.size(); i++) {
    max_diff = max(max_diff, v[i] - v[i - 1]);
  }
  return cos(max_diff / 2);
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  double a = get_outer_ratio(n);
  a *= get_coef(n, m);
  a /= get_inner_ratio(m);

  printf("%.18lf\n", a);

  return 0;
}
