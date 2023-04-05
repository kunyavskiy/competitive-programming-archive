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

#define TASKNAME "H"

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

vector<ll> a, b, c;

int main() {
  #define int ll
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%lld", &n);
  a.resize(n); b.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &a[i], &b[i]);
    if (a[i] > b[i]) swap(a[i], b[i]);
  }
  int m;
  scanf("%lld", &m);
  c.resize(m);
  for (int i = 0; i < m; i++) {
    scanf("%lld", &c[i]);
  }
  if (!m) {
    m = 1;
    c.push_back(-1000000100);
  }

  sort(c.begin(), c.end());

  ll ans = 0;

  vector<pair<ll, int>> ev;

  for (int i = 0; i < n; i++) {
    int id = (int)(lower_bound(c.begin(), c.end(), a[i]) - c.begin());
    if (id != (int)c.size() && c[id] <= b[i]) {
      ans += b[i] - a[i];
      continue;
    }
    ll l = 0x7fffffffffffLL;
    if (id != (int)c.size()) {
      l = min(l, (ll)c[id] - b[i]);
    }
    if (id != 0) {
      l = min(l, (ll)a[i] - c[id - 1]);
    }

    ans += b[i] - a[i] + 2LL * l;

    ev.push_back(make_pair(a[i] - l, -2));
    ev.push_back(make_pair(a[i]    , +2));
    ev.push_back(make_pair(b[i]    , +2));
    ev.push_back(make_pair(b[i] + l, -2));
  }


  if (!ev.empty()) {
    sort(ev.begin(), ev.end());

    int coef = 0;
    ll value = ans;
    int curx = ev[0].first;
    for (const auto& x : ev) {
      value += coef * 1LL * (x.first - curx);
      curx = x.first;
      ans = min(ans, value);
      coef += x.second;
    }
  }

  printf("%lld\n", ans);
  return 0;
}
