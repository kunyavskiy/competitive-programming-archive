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

ll dp[pw(11)][pw(11)];

void upd(ll& a, ll b) {
  a = max(a, b);
}

int main() {
#ifdef LOCAL
  freopen("kk.in", "r", stdin);
#endif
  int n;
  scanf("%d", &n);
  vector<ll> a(n), b(n);
  ll sa = 0, sb = 0;
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &a[i], &b[i]);
    sa += a[i];
    sb += b[i];
  }

  for (int i = 0; i < n; i++) {
    a[i] *= sb;
    b[i] *= sa;
  }



  for (int m1 = 0; m1 < pw(n); m1++) {
    for (int m2 = 0; m2 < pw(n); m2++) {
      for (int i = 0; i < n; i++) {
        upd(dp[m1 | pw(i)][m2], dp[m1][m2]);
        upd(dp[m1][m2 | pw(i)], dp[m1][m2]);
      }
      ll s1 = 0;
      ll s2 = 0;
      for (int i = 0; i < n; i++) {
        s1 += ((m1 >> i) & 1) * a[i];
        s2 += ((m2 >> i) & 1) * b[i];
      }
      for (int i = 0; i < n; i++) {
        if ((m1 & pw(i)) == 0 && (m2 & pw(i)) == 0) {
          ll L = max(s1, s2);
          ll R = min(s1 + a[i], s2 + b[i]);
          upd(dp[m1 | pw(i)][m2 | pw(i)], dp[m1][m2] + max(0ll, R - L));
        }
      }
    }
  }
  printf("%.17f\n", dp[pw(n) - 1][pw(n) - 1] * 1.0 / sa / sb);




  return 0;
}
