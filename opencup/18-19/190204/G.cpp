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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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
const double PI = acos(-1);
typedef long double dbl;

dbl sqr(dbl x) {
  return x * x;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    double kk, ll;
    scanf("%lf%lf", &kk, &ll);
    dbl k, l;
    k = kk;
    l = ll;
    dbl r1 = 0;
    dbl r2 = 0;
    if (l * 2 / PI < k) {
      r1 = l * l / PI / 2;
    }
    else {
      dbl L = k / 2.0;
      dbl R = 1e10;
      for (int i = 0; i < 80; i++) {
        dbl r = (L + R) / 2;
        dbl a = asin(k / 2.0 / r);
        if (r * 2 * PI > l + a * 2 * r) {
          R = r;
        }
        else {
          L = r;
        }
      }
      dbl r = (L + R) / 2;
      dbl a = asin(k / 2.0 / r);
      r2 = r * r * (PI - a);
      dbl h = sqrt(max((dbl)0, r * r - (k / 2) * (k / 2)));
      r2 += h * k / 2;
    }
    printf("%.20f\n", double(max(r1, r2)));

  }


  return 0;
}
