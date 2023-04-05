#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "D"

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

int A, B, n;
vector<int> l, r;

vector<vector<int>> g;
vector<int> color;

double cost[2];

double inside(int v) {
  return sqrt(B * 1LL * B + (r[v] - l[v]) * 1LL * (r[v] - l[v]));
}

double outside(int v) {
  return B + min(l[v] + r[v], 2 * A - l[v] - r[v]);
}


void dfs(int v, int c) {
  if (color[v] != -1) return;
  color[v] = c;
  for (int u : g[v]) {
    dfs(u, 1 - c);
  }
  cost[c] += inside(v);
  cost[1 - c] += outside(v);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d%d%d", &A, &B, &n);
  l.resize(n);
  r.resize(n);
  g.resize(n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &l[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &r[i]);
  }

  vector<int> order(n);
  for (int i = 0; i < n; i++) {
    order[i] = i;
  }

  sort(order.begin(), order.end(), [](int i, int j) { return l[i] < l[j]; });

  stack<pair<int, int>> s;

  for (int i : order) {
    int rg = r[i];
    pair<int, int> crg = make_pair(rg, i);
    while (!s.empty() && s.top().first >= rg) {
      crg = max(crg, s.top());
      g[i].push_back(s.top().second);
      g[s.top().second].push_back(i);
      s.pop();
    }
    s.push(crg);
  }

  color.resize(n, -1);

  double ans = 0;

  for (int i = 0; i < n; i++) {
    if (color[i] != -1) continue;
    cost[0] = cost[1] = 0;
    dfs(i, 0);
    ans += min(cost[0], cost[1]);
  }

  int maxr[2];
  maxr[0] = maxr[1] = -1;

  for (int i : order) {
    if (maxr[color[i]] >= r[i]) {
      printf("-1\n");
      return 0;
    }
    maxr[color[i]] = r[i];
  }

  printf("%.16f\n", ans);

  return 0;
}
