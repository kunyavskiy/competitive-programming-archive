#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
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
#include <random>

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

bool is_prime(int x) {
  if (x == 1) return 0;
  for (int i = 2; i * i <= x; i++) if (x % i == 0) return 0;
  return 1;
}

void upd(ll &x, ll y) {
  x = min(x, y);
}

ll solve(vector<int> a, ll x, ll y, ll z) {
  int n = a.size();
  auto aa = a;
  sort(aa.begin(), aa.end());
  aa.resize(unique(aa.begin(), aa.end()) - aa.begin());
  for (int &t : a) t = lower_bound(aa.begin(), aa.end(), t) - aa.begin();

  vector<vector<short>> lcp(n + 1, vector<short>(n + 1));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = n - 1; j >= 0; j--) {
      if (a[i] == a[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
      else lcp[i][j] = 0;
    }
  }

  int Q = 1e9 + mt19937(123)() % (int)5e7;
  while (!is_prime(Q)) Q++;

  const int max_len = n / 2 + 1;

  vector<vector<char>> can(n + 1, vector<char>(max_len));
  vector<vector<short>> nxt(n + 1, vector<short>(max_len, -1));
  for (int i = 0; i < n; i++) {
    int j = i;
    for (int len = 1; i + len <= n && len < max_len; len++) {
      while (j < n && (i + len > j || lcp[i][j] < len)) j++;
      if (j < n) nxt[i + len][len] = j;
    }
  }
  for (int r = n; r > 0; r--) {
    int j = r;
    for (int len = 1; r - len >= 0 && len < max_len; len++) {
      int start = r - len;
      while (j >= 0 && (j + len > start || lcp[j][start] < len)) j--;
      if (j >= 0) can[r][len] = 1;
    }
  }



  const ll INF = 1e18;
  vector<vector<ll>> dp(n + 1, vector<ll>(max_len, INF));
  dp[0][0] = 0;
  for (int i = 0; i <= n; i++) {
    for (int len = 0; len * 2 <= i; len++) {
      if (can[i][len]) {
        upd(dp[i][len], dp[i - len][0] + y + z);
      }
      upd(dp[i][0], dp[i][len]);
    }
    if (i == n) continue;
    for (int len = 0; len * 2 <= i; len++) {
      if (dp[i][len] == INF) continue;
      upd(dp[i + 1][0], dp[i][len] + x);
      if (nxt[i][len] != -1) {
        int j = nxt[i][len];
        upd(dp[j + len][len], dp[i][len] + z + (j - i) * x);
      }
    }
  }

  ll ans = *min_element(dp[n].begin(), dp[n].end());
  assert(ans < INF);
  return ans;
}

void test() {
  int n = 5000;
  vector<int> a(n);
  mt19937 rnd;
  for (int i = 0; i < n; i++) a[i] = rnd() % 10;
  solve(a, 1e9, 1e8, 1e8);
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
#endif
//  test();

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; test++) {
    int n, x, y, z;
    scanf("%d%d%d%d", &n, &x, &y, &z);
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    ll ans = solve(a, x, y, z);
    printf("Case #%d: %lld\n", test, ans);
  }

  return 0;
}
