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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;

const int INF = (int) 1.1e9;

class HungSolver {
    vector<vector<int>> a;
    vector<int> mt;
    int n;


    void iterate(int nv){
      vector<int> d(n+1, INF);
      vector<int> used(n+1, 0);
      vector<int> p(n+1, 0);
      vector<int> fl(n+1, 0);
      vector<int> fr(n+1, 0);

      d[n] = 0;
      int l = n;
      mt[n] = nv;

      while (mt[l] != -1){
        int k = mt[l];
        int nl = -1;
        used[l] = true;
        for (int i = 0; i < n; i++)
          if (!used[i]){ /*BOXNEXT*/
            if (d[i] > d[l] + a[k][i] + fl[k] + fr[i]) { /*BOXNEXT*/
              d[i] = d[l] + a[k][i] + fl[k] + fr[i];
              p[i] = l;
            }
            if (nl == -1 || d[nl] > d[i])
              nl = i;
          }

        int add = d[nl];

        for (int i = 0; i <= n; i++)
          if (used[i])
            fr[i] += add, fl[mt[i]] -= add;
          else
            d[i] -= add;
        l = nl;
      }

      while (l != n){
        mt[l] = mt[p[l]];
        l = p[l];
      }
    }
public:
    vector<int>& operator[](int id) {
      assert(0 <= id && id < n);
      return a[id];
    }

    int solve(){
      mt = vector<int>(n+1, -1);;
      for (int i = 0; i < n; i++)
        iterate(i);
      int ans = 0;
      for (int i = 0; i < n; i++)
        ans += a[mt[i]][i];
      return ans;
    }

    HungSolver(int n) {
      this->n = n;
      a.resize(n, vector<int>(n, 0));
    }
};
int _solved, _testNum;

class AbstractSolver {
    char *_ob;
    int _ob_pos;
    const int _buffer_size = 16 * (1 << 20);
public:
    int _testId;

    AbstractSolver(int _testId) : _testId(_testId) {
      _ob = (char *) malloc(_buffer_size + 10);
      _ob_pos = 0;
      printf("Case #%d: ", _testId);
    }

    __attribute__((format(printf, 2, 3)))
    void printf(const char *format, ...) {
      va_list ap;
      va_start (ap, format);
      _ob_pos += vsnprintf(_ob + _ob_pos, _buffer_size - _ob_pos, format, ap);
      va_end (ap);
      assert(_ob_pos < _buffer_size - 10);
    }

    virtual void write() {
      _ob[_ob_pos] = 0;
      ::printf("%s", _ob);
    }

    virtual void solve() = 0;;

    virtual void read() = 0;

    void run() {
      solve();
#ifdef _OPENMP
#pragma omp critical 
#endif
      {
        _solved++;
        if ((_solved - 1) * 100 / _testNum != _solved * 100 / _testNum || _solved <= 20 || _testNum - _solved <= 20)
                TIMESTAMPf("%d%% of tests solved (%d/%d, %d more)", _solved * 100 / _testNum, _solved, _testNum,
                           _testNum - _solved);
      }
    }
};


void PreCalc() {
}

class Solver : public AbstractSolver {
public:
    Solver(int _testId) : AbstractSolver(_testId) { }

    vector<vector<int>> g;
    vector<vector<int>> cost;

    vector<vector<vector<int>>> dp;

    int k, p, n;
    void read() {
      scanf("%d%d%d",&n,&k,&p);
      g.resize(n);
      cost.resize(n);
      for (int i = 0; i < n; i++) {
        cost[i].resize(k);
        for (int j = 0; j < k; j++)
          scanf("%d",&cost[i][j]);
      }
      for (int i = 0; i < n-1; i++) {
        int a, b;
        scanf("%d%d",&a,&b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
      }
    }

    void dfs(int v, int par) {
      for (int u : g[v]) {
        if (u != par) {
          dfs(u, v);
        }
      }
      for (int myc = 0; myc < k; myc++) {
        for (int parc = 0; parc < k; parc++) {
          if (par == -1 && parc != 0) continue;
          int& ans = dp[v][parc][myc];
          ans = p;
          for (int u : g[v]) {
            if (u == par) continue;
            ans += *min_element(dp[u][myc].begin(), dp[u][myc].end());
          }
          if ((int)g[v].size() <= k) {
            HungSolver s(k - (par != -1));
            int id = 0;
            for (int u : g[v]) {
              if (u == par) continue;
              for (int j = 0; j < k; j++) {
                if (j == parc && par != -1) continue;
                s[id][j - (parc < j && par != -1)] = dp[u][myc][j];
              }
              id++;
            }
            ans = min(ans, s.solve());
          }
          ans += cost[v][myc];
        }
      }
    }

    void solve() {
      dp.resize(n, vector<vector<int>>(k, vector<int>(k, -1)));
      dfs(0, -1);
      int ans = INF;
      for (int i = 0; i < k; i++) {
        ans = min(ans, dp[0][0][i]);
      }
      printf("%d\n", ans);
    }

};

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &_testNum);

  vector < Solver * > solvers(_testNum);

  for (int i = 0; i < _testNum; i++) {
    solvers[i] = new Solver(i + 1);
    solvers[i]->read();
  }

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < _testNum; i++) {
    solvers[i]->run();
  }

  for (int i = 0; i < _testNum; i++) {
    solvers[i]->write();
  }

  TIMESTAMP(end);
  return 0;
}
