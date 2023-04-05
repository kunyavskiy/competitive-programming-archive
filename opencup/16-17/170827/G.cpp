#include <iostream>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  vector<pair<int, int>> d(n);
  vector<pair<int, int>> p(n);
  p[0] = {-1, -1};
  d[0] = {INT32_MAX, INT32_MIN};
  for (int i = 0; i < n - 1; i++) {
    d[i + 1] = {INT32_MIN, INT32_MAX};
    if (a[i + 1] > a[i]) {
      if (d[i + 1].first < d[i].first) {
        d[i + 1].first = d[i].first;
        p[i + 1].first = 0;
      }
    }
    if (a[i + 1] < d[i].first) {
      if (d[i + 1].second > a[i]) {
        d[i + 1].second = a[i];
        p[i + 1].second = 0;
      }
    }
    if (a[i + 1] < a[i]) {
      if (d[i + 1].second > d[i].second) {
        d[i + 1].second = d[i].second;
        p[i + 1].second = 1;
      }
    }
    if (a[i + 1] > d[i].second) {
      if (d[i + 1].first < a[i]) {
        d[i + 1].first = a[i];
        p[i + 1].first = 1;
      }
    }
  }
  int c = -1;
  if (d[n - 1].first > INT32_MIN) {
    c = 0;
  }
  if (d[n - 1].second < INT32_MAX) {
    c = 1;
  }
  if (c == -1) {
    puts("NO");
  } else {
    vector<int> fs;
    vector<int> sc;
    for (int i = n - 1; i >= 0; i--) {
      if (c == 0) {
        fs.push_back(a[i]);
        c = p[i].first;
      } else {
        sc.push_back(a[i]);
        c = p[i].second;
      }
    }
    puts("YES");
    printf("%d", (int)fs.size());
    for (int i = 0; i < (int)fs.size(); i++) {
      printf(" %d", fs[fs.size() - i - 1]);
    }
    printf("\n%d", (int)sc.size());
    for (int i = 0; i < (int)sc.size(); i++) {
      printf(" %d", sc[sc.size() - i - 1]);
    }
    puts("");
  }
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    solve();
  }

  return 0;
}
