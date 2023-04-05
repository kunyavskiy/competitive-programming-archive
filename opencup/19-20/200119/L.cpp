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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(ll a, ll b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

const ll INF = ll(1.1e18);
ll C;
ll MAX;

ll find_max(ll x) {
  if (x <= 0) {
    return INF;
  }
  if (C / x / x / x >= 1) {
    return C / x / x;
  }
  ll T = C / x;
  ll res = sqrt(T);
  while (res * res <= T) res++;
  res--;
  return res;
  ll L = 0;
  ll R = C + 1;
  while (L + 1 < R) {
    ll M = (L + R) / 2;
    assert(M > 0);
    if (C / x / M / min(x, M) >= 1) {
      L = M;
    } else {
      R = M;
    }
  }
  return L;
}

vector<ll> arr;
vector<int> pref;

void init() {
  arr.resize(MAX);
  for (int i = 1; i <= MAX; ++i) {
    arr[i - 1] = (C / i / i);
  }
  pref.resize(MAX + 1);
  for (int i = 1; i <= MAX; ++i) {
    pref[i] = pref[i - 1];
    add(pref[i], arr[i - 1] % MOD);
  }
}

int sum(int L, int R) {
  return (ll(L + R) * (R - L + 1) / 2) % MOD;
  ll A = (L + R);
  ll B = (R - L + 1);
  if (A % 2 == 0) {
    A /= 2;
  } else {
    B /= 2;
  }
  return mul(A, B);
}

int calc(ll A, ll B) {
  eprintf("A %lld B %lld MAX %lld\n", A, B, MAX);
  A = min(A, MAX);

  int X = lower_bound(arr.begin(), arr.end(), B, greater<>()) - arr.begin();
  eprintf("X %d\n", X);
  int ans = 0;
  if (X + 1 <= A) {
    add(ans, pref[A]);
    sub(ans, pref[X]);
    sub(ans, sum(X + 1, A));
  }
  eprintf("ans1 %d\n", ans);

  X = min<ll>(min(A, B), X);
  if (1 <= X) {
    add(ans, mul(B % MOD, X));
    sub(ans, sum(1, X));
  }
  add(ans, B % MOD);
  eprintf("ans %d\n", ans);
  return ans;
}

void combine(int &a, int b) {
  if (a == -1 || b == -1) {
    a = -1;
  } else {
    add(a, b);
  }
}

#ifdef LOCAL
#define STUPID
//#define GEN
#endif

int stupid(vector<ll> v) {
  v.push_back(0);
  int n = v.size();
  int MX = max(C + 1, *max_element(v.begin(), v.end()));
  vector<vector<int>> dp(n + 1, vector<int>(MX + 1));
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int a = 0; a <= MX; ++a) {
      if (v[i] != -1 && v[i] != a) {
        continue;
      }
      for (int b = 0; b <= MX; ++b) {
        if (a == 0 || b == 0 || C / a / b / min(a, b) >= 1) {
          combine(dp[i + 1][a], dp[i][b]);
          if (dp[i][b] && (a > C && v[i] == -1)) {
            dp[i + 1][a] = -1;
          }
//          eprintf("dp[%d][%d] = %d\n", i + 1, a, dp[i + 1][a]);
        }
      }
    }
  }
  return dp[n][0];
}

bool solve() {
  int n;
#ifdef GEN
  n = rand() % 30 + 1;
  C = rand() % 1000;
#else
  if (scanf("%d", &n) != 1) {
    return false;
  }
  scanf("%lld", &C);
  vector<ll> a(n + 2, 0);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
  }
  n += 2;
#endif
  MAX = 0;
  while (MAX * MAX * MAX <= C) {
    MAX++;
  }
  MAX--;

  init();

#ifdef GEN
  int FROM = 1;
  int TO = C + 10;
  vector<ll> a;
  for (int i = 0; int(a.size()) < n; ++i) {
    int k = rand() % 2 + 1;
    a.push_back(rand() % (TO - FROM + 1) + FROM);
    for (int j = 0; j < k; ++j) {
      a.push_back(-1);
    }
//    a.push_back(rand() % (C + 2));
  }
  a.push_back(rand() % (TO - FROM + 1) + FROM);
  n = int(a.size());
#endif

  eprintf("C %lld arr: ", C);
  for (int i = 0; i < n; ++i) {
    eprintf("%lld ", a[i]);
  }
  eprintf("\n");

  int ans = 1;
  for (int i = 0; i < n; ++i) {
    if (a[i] != -1) {
      if (i != 0 && a[i - 1] != -1 && a[i] && a[i - 1] && C / a[i] / a[i - 1] / min(a[i], a[i - 1]) < 1) {
        printf("0\n");
        return true;
      }
      continue;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (a[i] != -1) { continue; }

    ll A = (i == 0 ? INF : find_max(a[i - 1]));
    if (i == n - 1 || a[i + 1] != -1) {
      ll B = (i == n - 1 ? INF : find_max(a[i + 1]));
      eprintf("i %d A %lld B %lld\n", i, A, B);
      if (A == INF && B == INF) {
        printf("-1\n");
        return true;
      }
      ans = mul(ans, (min(A, B) + 1) % MOD);
    } else {
      ++i;
      ll B = (i == n - 1 ? INF : find_max(a[i + 1]));
      eprintf("i %d..%d A %lld B %lld\n", i - 1, i, A, B);
      if (A == INF || B == INF) {
        printf("-1\n");
        return true;
      }
      int cur = 0;
      add(cur, (min(MAX, min(A, B)) + 1) % MOD);
      add(cur, calc(A, B));
      add(cur, calc(B, A));
      ans = mul(ans, cur);
    }
  }
  printf("%d\n", ans);
#ifdef STUPID
  if (C <= 1000) {
    int stupid_ans = stupid(a);
    eprintf("ans %d stupid_ans = %d\n", ans, stupid_ans);
    assert(ans == stupid_ans);
  }
#endif
  fflush(stdout);
  return true;
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  srand(time(0));

  while (solve());

  return 0;
}
