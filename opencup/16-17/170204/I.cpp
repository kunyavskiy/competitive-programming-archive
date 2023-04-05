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

#define TASKNAME "I"

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

const int LOG = 20;
const int N = (int) 2e5 + 100;
vector <int> g[N];
int h[N], d[N][4];
int par[N][LOG];
int parD[N][LOG];
int parDback[N][LOG];

int goUp(int v, int x)
{
  for (int i = 0; i < LOG; i++)
    if (x & (1 << i))
      v = par[v][i];
  return v;
}

int LCA(int a, int b)
{
  if (h[a] < h[b] )
    swap(a, b);
  a = goUp(a, h[a] - h[b] );
  if (a == b) return a;
  for (int i = LOG - 1; i >= 0; i--)
  {
    if (par[a][i] != par[b][i])
    {
      a = par[a][i];
      b = par[b][i];
    }
  }
  return par[a][0];
}

void dfs(int v, int p, int ch)
{
  h[v] = ch;
  par[v][0] = p;
  d[v][0] = 0;
  d[v][1] = 0;
  d[v][2] = 0;
  for (int i = 1; i < LOG; i++)
    par[v][i] = par[par[v][i - 1]][i - 1];
  for (int to : g[v] )
  {
    if (to == p) continue;
    dfs(to, v, ch + 1);
    int nd = d[to][0] + 1;
    d[v][3] = nd;
    sort(d[v], d[v] + 4);
    reverse(d[v], d[v] + 4);
  }
  for (int to : g[v] )
  {
    if (to == p) continue;
    int nd = d[to][0] + 1;
    int alt = d[v][0];
    if (alt == nd)
      alt = d[v][1];
    parD[to][0] = alt + 1;
    parDback[to][0] = alt - 1;
  }
}

const int X = 1000;

int getMax(int v, int x)
{
  if (x < 0) return -X;
  int ans = 0;
  int base = 0;
  for (int i = 0; i < LOG; i++)
    if (x & (1 << i) )
    {
      ans = max(ans, parD[v][i] + base);
      v = par[v][i];
      base += (1 << i);
    }
  return ans;
}

int getMaxBack(int v, int x)
{
  if (x < 0) return -X;
  int ans = 0;
  int base = x;

  for (int i = 0; i < LOG; i++)
    if (x & (1 << i) )
    {
      ans = max(ans, parDback[v][i] + base);
      base -= (1 << i);
    }
  return ans;
}

bool canRun(int a, int ad, int b, int bd)
{
  int l = LCA(a, b);
  int dist = h[a] + h[b] - 2 * h[l];

  if (bd >= dist) return false;

  if (l != a && d[a][0] >= ad) return true;

  int aup = min(h[a] - h[l] - 1, dist - bd - 1);
  if (getMax(a, aup) >= ad) return true;

  if (bd >= h[b] - h[l] ) return false;

  if (h[a] - h[l] + getMax(l, h[l] ) >= ad) return true;

  if (b == l) throw;

  vector <int> ds;
  int chb = goUp(b, h[b] - h[l] - 1);
  ds.push_back(d[chb][0] + 1);

  if (a != l) {
    int cha = goUp(a, h[a] - h[l] - 1);
    ds.push_back(d[cha][0] + 1);
  }
  sort(ds.begin(), ds.end() );
  reverse(ds.begin(), ds.end() );
  int ptr = 0;
  for (int x : ds)
    if (d[l][ptr] == x)
      ptr++;

  if (h[a] - h[l] + d[l][ptr] >= ad) return true;

  int ldown = max(0, h[b] - h[l] - bd - 1);
  if (getMaxBack(goUp(b, bd), ldown) + dist - bd >= ad) return true;

  return false;
}



struct State
{
  int maskA, maskB, vA, vB;
  State() : maskA(), maskB(), vA(), vB() {}

  State(int _maskA, int _maskB, int _vA, int _vB) : maskA(_maskA), maskB(_maskB), vA(_vA), vB(_vB) {}


  int score() {
    return __builtin_popcount(maskA) - __builtin_popcount(maskB);
  }

  bool operator < (const State &A) const
  {
    if (maskA != A.maskA) return maskA < A.maskA;
    if (maskB != A.maskB) return maskB < A.maskB;
    if (vA != A.vA) return vA < A.vA;
    if (vB != A.vB) return vB < A.vB;
    return false;
  }
};

map <pair <State, int>, int> M;

void clear(int n)
{
  M.clear();

  for (int i = 0; i < n; i++)
    g[i].clear();
}

int solveSlow(State &s, int t)
{
  if (t == 0) return s.score();
  if (M.count(make_pair(s, t) ) ) return M[make_pair(s, t)];
/*  int ans = -100;
  for (int to : g[s.vA] )
  {
    State ns = State();
  }
*/
  return 100;
}

int solveSlow(int qa, int qb, int qt)
{
  State s = State(1 << qa, qa, 1 << qb, qb);
  return solveSlow(s, qt);
}


bool solve()
{
  int n, q;
  if (scanf("%d%d", &n, &q) <= 0) return false;

  clear(n);

  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector <int> qa, qb, qt;

  for (int i = 0; i < q; i++)
  {
    int a, b, t;
    scanf("%d%d%d", &a, &b, &t);
    a--;
    b--;
    qa.push_back(a);
    qb.push_back(b);
    qt.push_back(t);
  }

  dfs(0, 0, 0);
  for (int i = 1; i < LOG; i++)
    for (int v = 0; v < n; v++)
      parD[v][i] = max(parD[v][i - 1], parD[par[v][i - 1] ][i - 1] + (1 << (i - 1) ) );

  for (int i = 1; i < LOG; i++)
    for (int v = 0; v < n; v++)
      parDback[v][i] = max(parDback[v][i - 1], parDback[par[v][i - 1] ][i - 1] - (1 << (i - 1) ) );


  for (int i = 0; i < q; i++)
  {
    int a = qa[i], b = qb[i], t = qt[i];

//    int ansSlow = solveSlow(n, a, b, t);

    int l = LCA(a, b);
    int dist = h[a] + h[b] - 2 * h[l];
    int ans = -100;
    if (dist % 2 == 1)
    {
      if (t % 2 == 0)
        ans = 0;
      else if (t % 2 == 1) {
        ans = 2;
        if (canRun(b, t / 2, a, (t + 1) / 2) )
          ans = 1;
      }
      else throw;
    }
    else if (dist % 2 == 0)
    {
      if (t % 2 == 0) {
        ans = -1;
        if (canRun(a, (t + 1) / 2, b, t / 2) )
          ans = 0;
      }
      else if (t % 2 == 1)
        ans = 1;
      else throw;
    }
    else throw;
    if (ans == -100) throw;

    printf("%d\n", ans);
  }

  return true;
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  while (solve() );

  return 0;
}
