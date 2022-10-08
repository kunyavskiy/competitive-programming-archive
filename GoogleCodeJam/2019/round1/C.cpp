#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

struct dsu {
  vector<int> p;
  vector<int> size;
public:
  explicit dsu(int n) : p(n), size(n, 1) {
    for (int i = 0; i < n; i++) {
      p[i] = i;
    }
  }

  int get(int x) {
    if (x == p[x]) return x;
    return p[x] = get(p[x]);
  }

  int getSize(int x) {
    return size[get(x)];
  }

  void join(int x, int y) {
    x = get(x); y = get(y);
    if (x == y) return;
    if (size[x] > size[y]) swap(x, y);
    p[x] = y;
    size[y] += size[x];
  }
};

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  ll ans = n * 1LL * (n + 1) / 2;
  vector<pair<int, int>> v[2];
  v[0] = v[1] = vector<pair<int, int>>(n);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &v[i][j].first);
      v[i][j].second = j;
    }
    sort(v[i].begin(), v[i].end());
  }
  for (int it = 0; it < 2; it++) {
    dsu d(n);
    vector<int> used(n);

    auto ok = [&](int x) { return x >= 0 && x < n && used[x] == 2; };

    auto use = [&](int x) {
      used[x]++;
      if (used[x] == 2) {
        if (ok(x - 1)) {
          d.join(x - 1, x);
        }
        if (ok(x + 1)) {
          d.join(x + 1, x);
        }
      }
    };

    int ptr = 0;

    for (int i = 0; i < n; i++) {
      while (ptr < n && v[1][ptr].first < v[0][i].first - k) {
        use(v[1][ptr].second);
        ptr++;
      }

      int pos = v[0][i].second;
      int lf = (ok(pos - 1)) ? d.getSize(pos - 1) : 0;
      int rg = (ok(pos + 1)) ? d.getSize(pos + 1) : 0;
      use(pos);
      if (used[pos] == 2) {
        ans -= (lf + 1) * 1LL * (rg + 1);
        eprintf("-%lld for %d on %d\n", (lf + 1) * 1LL * (rg + 1), pos, it);
      }
    }

    v[0].swap(v[1]);
  }

  printf("%lld\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
