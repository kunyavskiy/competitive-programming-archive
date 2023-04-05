#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "E"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

const int P = int(1e9) + 7;

int sum(int a, int b) {
  if ((a += b) >= P) {
    a -= P;
  }
  return a;
}

int prod(int a, int b) {
  return (int)((ll(a) * b) % P);
}

int& add(int &a, int b) {
  return a = sum(a, b);
}

int dfs1(int s, int par, int k, const vector <vector<int>> &ed, vector<int> & size) {
  size[s] = 1;
  for (int v : ed[s]) {
    if (v == par) { continue; }
    size[s] += dfs1(v, s, k, ed, size);
    if (size[s] > k) { size[s] = k; }
  }
  return size[s];
}

void dfs2(int s, int par, int k, const vector<vector<int>> &ed, const vector<int>&size, vector<vector<int>>&dp) {
  dp.clear();
  dp.assign(3, vector<int>(size[s] + 1, 0));
  vector<vector<int>> dp2 = dp;
  dp[0][0] = 1;
  dp[1][1] = 1;
  vector<vector<int>> chDp;
  for (int v : ed[s]) {
    if (v == par) { continue; }
    dfs2(v, s, k, ed, size, chDp);
    for (int x = 0; x <= size[v]; ++x) {
      for (int y = 0; x + y <= size[s]; ++y) {
        int z = x + y;
        add(dp2[0][z], prod(dp[0][y], sum(chDp[0][x], chDp[2][x])));
        add(dp2[1][z], prod(dp[1][y], chDp[0][x]));
        add(dp2[2][z], prod(dp[1][y], sum(chDp[1][x], chDp[2][x])));
        add(dp2[2][z], prod(dp[2][y], sum(chDp[0][x], sum(chDp[1][x], chDp[2][x]))));
      }
    }
    dp.swap(dp2);
    eprintf("s %d v %d\n", s, v);
    for (int p = 0; p < 3; ++p) {
      eprintf("dp[%d] = ", p);
      for (int y = 0; y <= size[s]; ++y) {
        eprintf("%d ", dp[p][y]);
        dp2[p][y] = 0;
      }
      eprintf("\n");
    }
  }
}

bool solve() {
  int n, k;
  if (scanf("%d%d", &n, &k) != 2)  return false;
  vector <vector<int>> ed(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    ed[u].push_back(v);
    ed[v].push_back(u);
  }
  vector<int> size(n);
  dfs1(0, -1, k, ed, size);
  vector<vector<int>> dp;
  dfs2(0, -1, k, ed, size, dp);
  printf("%d\n", sum(dp[0][k], dp[2][k]));
  return true;
}

int main() {
  #ifdef LOCAL
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
  #endif

  while (solve());

  return 0;
}
