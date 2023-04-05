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

#define TASKNAME "B"

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


ll check(vector<int> a, int d0, int m) {
  ll ans = 0;
  int n = (int)a.size();
  for (int i = 0; i < n; i++) {
    int diff = i != 0 ? a[i] : d0;
    ans += min(diff, m - diff);
    a[i] = (a[i] - diff + m) % m;
    int next = (i == n - 1) ? 0 : (i + 1);
    a[next] = (a[next] - diff + m) % m;
  }
  assert(a[0] == 0);
  return ans;
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> a(n), d(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
      int b;
      scanf("%d", &b);
      a[i] = (b - a[i] + m) % m;
    }
    d[0] = 0;
    for (int i = 1; i < n; i++) {
      d[i] = (a[i] - d[i - 1] + m) % m;
    }
    d[0] = (a[0] - d[n- 1] + m) % m;
    if (n % 2 != 0) {
      if (m % 2 == 0) {
        if (d[0] % 2 != 0) {
          printf("-1\n");
        } else {
          printf("%lld\n", min(check(a, d[0] / 2, m), check(a, d[0] / 2 + m / 2, m)));
        }
      } else {
        if (d[0] % 2 == 0) {
          printf("%lld\n", check(a, d[0] / 2, m));
        } else {
          printf("%lld\n", check(a, (d[0] + m) / 2, m));
        }
      }
    } else {
      if (d[0] != 0) {
        printf("-1\n");
        continue;
      }
      vector<pair<int, int>> ev;
      int curd = 0;
      ll curv = 0;
      int m1 = m / 2;
      int m2 = (m + 1) / 2;
      for (int i = 0; i < n; i++) {
        curv += min(d[i], m - d[i]);

        if (i % 2 == 0) {
          ev.push_back(make_pair((m - d[i]) % m, 2));
          ev.push_back(make_pair((m - d[i] + m1) % m, -1));
          ev.push_back(make_pair((m - d[i] + m2) % m, -1));

          if (0 < d[i] && d[i] <= m1) {
            curd += 1;
          } else if (m1 < d[i] && d[i] <= m2) {
            curd += 0;
          } else {
            curd += -1;
          }
        } else {
          ev.push_back(make_pair(d[i], 2));
          ev.push_back(make_pair((d[i] - m1 + m) % m, -1));
          ev.push_back(make_pair((d[i] - m2 + m) % m, -1));

          if (0 <= d[i] && d[i] < m1) {
            curd += -1;
          } else if (m1 <= d[i] && d[i] < m2) {
            curd += 0;
          } else {
            curd += 1;
          }
        }
      }
      ev.push_back(make_pair(m, 0));
      sort(ev.begin(), ev.end());

      int last = 0;
      ll ans = 1LL << 60;
      for (const auto& x : ev) {
        curv += curd * 1LL * (x.first - last);
        ans = min(ans, curv);
        curd += x.second;
        last = x.first;
      }

      printf("%lld\n", ans);
    }
  }

  return 0;
}
