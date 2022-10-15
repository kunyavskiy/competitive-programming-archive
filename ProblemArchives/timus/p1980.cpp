#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <sstream>
//#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME ""

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#ifndef LOCAL
#undef assert
void assert(bool x) {
  if (!x) printf("%d\n", 5 / 0);
}
void assert2(bool x) {
  if (!x) {
    int *tmp = new int[1];
    tmp[int(1e5)] = 100 / 23;
  }
}
#else
#define assert2 assert
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef linux
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

const int inf = 1e9;
const double eps = 1e-9;
const double INF = inf;
const double EPS = eps;

struct Edge {
  int to, id;
  double len, maxv;
};

const int MAXN = 11000;

int n;
vector<Edge> es[MAXN];
double d[MAXN];
int fr[MAXN], fre[MAXN];
bool was[MAXN];

double getT(double maxvplus, int st, int en) {
  for (int i = 0; i < n; i++) d[i] = 1e100, fr[i] = fre[i] = -1, was[i] = false;

  priority_queue<pair<double, int> > q;
  d[st] = 0;
  q.push(mp(-d[st], st));
  while (!q.empty()) {
    double cd = -q.top().first;
    int v = q.top().second;
    q.pop();
    if (was[v]) continue;

    was[v] = true;
    for (int i = 0; i < sz(es[v]); i++) {
      int b = es[v][i].to;
      double cw = es[v][i].len / (es[v][i].maxv + maxvplus);
      double nd = cd + cw;
      if (d[b] <= nd + eps) continue;

      d[b] = nd;
      fr[b] = v; fre[b] = es[v][i].id;
      q.push(mp(-d[b], b));
    }
  }
  return d[en];
}

int main(){     
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  int m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < n; i++)
      es[i].clear();

    for (int i = 0; i < m; i++) {
      int a, b; double s, l;
      scanf("%d%d%lf%lf", &a, &b, &s, &l), a--, b--;

      Edge e;
      e.id = i;
      e.to = b;
      e.len = l;
      e.maxv = s;
      es[a].pb(e);

      e.to = a;
      es[b].pb(e);
    }

    double maxt;
    scanf("%lf", &maxt);
    double L = 0, R = 1e9;
    for (int step = 0; step < 60; step++) {
      double M = (L + R) / 2;
      double curt = getT(M, 0, n - 1);
      if (curt <= maxt) R = M;
      else L = M;
    }

    double ans = (L + R) / 2;
    getT(ans, 0, n - 1);
    vi roads;
    for (int v = n - 1; fr[v] >= 0; v = fr[v])
      roads.pb(fre[v]);
    reverse(roads.begin(), roads.end());

    printf("%.8lf %d\n", ans, sz(roads));
    for (int i = 0; i < sz(roads); i++)
      printf("%d%c", roads[i] + 1, "\n "[i + 1 < sz(roads)]);

    #ifndef LOCAL
    break;
    #endif
  }

  TIMESTAMP(end);
  return 0;
}
