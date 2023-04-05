#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "H"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__),fflush(stderr)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector <ll> vll;
typedef vector<int> vi;
typedef vector <vi> vvi;
typedef vector<bool> vb;
typedef vector <vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;

const int inf = 1e9;
const ld eps = 1e-9;
const int INF = inf;
const ld EPS = eps;

#ifdef LOCAL
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {
};
#endif

/*Template end*/

int get(const vector<vector<int>> &st, const vector<int> & logLen, int (*func)(int,int), int defVal, int R, int len) {
  if (len == 0) { return defVal; }
  int k = logLen[len];
  int val1 = st[k][R - (1 << k) + 1];
  int val2 = st[k][R - len + 1];
  return func(val1, val2) * len;
}

int myMin(int a, int b) {
  return min(a, b);
}

int myMax(int a, int b) {
  return max(a, b);
}

int solve() {
  int n;
  if (scanf("%d", &n) != 1) return 0;
  eprintf("n = %d\n", n);

  vector <int> t(n), a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &t[i], &a[i]);
  }
  vector <int> sum(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    sum[i + 1] = sum[i] + a[i];
  }
  int logN = 0;
  while ((1 << logN) < n) {
    logN++;
  }
  logN++;
  eprintf("logN = %d\n", logN);
  vector <int> logLen(n + 1);
  for (int i = 0; i < logN; ++i) {
    for (int j = (1 << i); j <= n && j < (1 << (i + 1)); ++j) {
      logLen[j] = i;
    }
  }
  vector <vector<int>> stMin(logN), stMax(logN);
  stMin[0] = a;
  stMax[0] = a;
  for (int i = 1; i < logN; ++i) {
    stMin[i] = vector<int>(n);
    stMax[i] = vector<int>(n);
    for (int j = 0; j + (1 << (i - 1)) < n; ++j) {
      stMin[i][j] = min(stMin[i - 1][j], stMin[i - 1][j + (1 << (i - 1))]);
      stMax[i][j] = max(stMax[i - 1][j], stMax[i - 1][j + (1 << (i - 1))]);
    }
  }
  int q;
  scanf("%d", &q);
  eprintf("q = %d\n", q);
  for (int ii = 0; ii < q; ++ii) {
    static char s1[10], s2[10];
    int dt;
    scanf("%s%s%d", s1, s2, &dt);
    int res = 0;
    int sign = (s1[0] == 'g' ? 1 : -1);
    for (int i = 0, j = 0; i < n; ++i) {
      while (t[j] + dt < t[i]) {
        ++j;
      }
      eprintf("dt %d i %d j %d\n", dt, i, j);
      int len = i - j;
      if (len == 0) { continue; }
      int val1 = a[i] * len;
      int val2;
      if (!strcmp(s2, "avg")) {
        val2 = sum[i] - sum[j];
      } else if (!strcmp(s2, "min")) {
        val2 = get(stMin, logLen, myMin, INF, i - 1, len);
      } else if (!strcmp(s2, "max")) {
        val2 = get(stMax, logLen, myMax, -INF, i - 1, len);
      } else {
        assert(0);
      }
      if (sign * val1 > sign * val2) {
        ++res;
        eprintf("val1 %d val2 %d OK\n", val1, val2);
      } else {
        eprintf("val1 %d val2 %d NO\n", val1, val2);
      }
    }
    printf("%d\n", res);
  }
  return 1;
}

int main() {
  #ifdef LOCAL
  freopen("H.in", "r", stdin);
  freopen("H.out", "w", stdout);
  #endif

  while (solve());

  return 0;
}
