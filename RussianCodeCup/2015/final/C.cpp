//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

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

const int MAXN = 110000;

vector<int> g[MAXN], gt[MAXN];

set<pair<pair<int, int>, int> > s;
vector<int> deg;

int ts[MAXN];
int bts[MAXN];
bool used[MAXN];
int after[MAXN];
int rptr;
int proc_ptr;

void dfs(int v, int a) {
  assert(!used[v]);
  used[v] = true;
  after[v] = a;
  for (int u : g[v])
    if (!used[u])
      dfs(u, a);
}

void process() {
  eprintf("process\n");
  for (; proc_ptr >= 0; proc_ptr--) {
    if (ts[proc_ptr] != -1) {
      eprintf("got %d\n", ts[proc_ptr] + 1);
      assert(deg[ts[proc_ptr]] == 0);
    } else {
      if (s.empty()) return;
      assert(s.begin()->first.first == 0);
      ts[proc_ptr] = s.begin()->second;
      eprintf("set %d\n", ts[proc_ptr] + 1);
      s.erase(s.begin());
    }
    for (int u : gt[ts[proc_ptr]]) {
      if (s.find(mp(mp(deg[u], after[u]), u)) != s.end()) {
        s.erase (mp (mp(deg[u], after[u]), u));
        deg[u]--;
        s.insert (mp (mp(deg[u], after[u]), u));
      } else {
        deg[u]--;
      }
    }
  }
}

void solve() {
  int n, m;
  scanf ("%d%d", &n, &m);
  eprintf("===================\n%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    g[i].clear ();
    gt[i].clear ();
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    assert(scanf ("%d%d", &a, &b) == 2);
    --a, --b;
    g[a].pb (b);
    gt[b].pb (a);
  }
  for (int i = 0; i < n; i++) {
    used[i] = 0;
    after[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    scanf ("%d", &bts[i]);
    bts[i]--;
  }
  for (int i = 0; i < n; i++)
    ts[i] = -1;
  for (int i = 0; i < n; i++)
    if (bts[i] != -1)
      ts[bts[i]] = i;

  s.clear();
  deg = vector<int>(n);
  for (int i = 0; i < n; i++) {
    deg[i] = g[i].size();
  }

  rptr = proc_ptr = n - 1;
  while (rptr >= 0) {
    if (ts[rptr] != -1) {
      dfs (ts[rptr], -rptr);
    }
    rptr--;
  }

  for (int i = 0; i < n; i++)
    if (bts[i] == -1)
      s.insert(mp(mp(deg[i], after[i]), i));
  process ();

  for (int i = 0; i < n; i++) {
    assert(ts[i] != -1 && (bts[ts[i]] == -1 || bts[ts[i]] == i));
    bts[ts[i]] = i;
  }
  for (int i = 0; i < n; i++)
    printf ("%d%c", bts[i] + 1, " \n"[i == n - 1]);
  for (int i = 0; i < n; i++)
    for (int u : g[i])
      if (bts[u] < bts[i]) {
        eprintf("%d -> %d\n", i+1, u+1);
        assert(0);
      }
}

int main() {
  #ifdef LOCAL
  assert(freopen (TASKNAME".in", "r", stdin));
  assert(freopen (TASKNAME".out", "w", stdout));
  #endif

  int t;
  scanf ("%d", &t);
  while (t --> 0) {
    solve();
  }
      
  return 0;
}
