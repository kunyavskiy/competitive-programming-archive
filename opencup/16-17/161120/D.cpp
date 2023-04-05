#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "D"

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
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);

  vector<ll> v(n);

  ll g = 0;
  ll sum = 0;

  for (ll& x : v) {
    scanf("%lld", &x);
    sum += x;
    g ^= x;
  }

  if (g == 0) {
    ll all = 0;
    for (ll x : v) {
      all |= x;
    }
    all = all & ~(all - 1);
    for (int i = 0; i < n; i++) {
      if (v[i] & all) {
        printf("%lld\n", sum);
        printf("%d %d\n", i + 1, 1);
        return 0;
      }
    }
    assert(0);
  }

  ll ans = sum;
  int bi = 0;
  ll bs = 0;

  for (int i = 0; i < n; i++) {
    ll y = g ^ v[i];
    if (y >= v[i]) continue;
    ll cur = sum - v[i] + y;
    if (cur < ans) {
      ans = cur;
      bi = i + 1;
      bs = v[i] - y;
    }
  }

  assert(bi);
  printf("%lld\n%d %lld\n", ans + 1, bi, bs);

  return 0;
}
