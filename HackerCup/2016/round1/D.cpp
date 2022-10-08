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
      printf("Case #%d:\n", _testId);
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

    vector<vector<int>> w;
    
    void read() {
      int n;
      scanf("%d",&n);
      w.resize(n, vector<int>(n, 0));
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          scanf("%d", &w[i][j]);
    }

    void solve() {
      int n = (int) w.size();
      vector<int> dp(1 << n);
      vector<int> ansl(n, n / 2 + 1);
      vector<int> ansr(n, 1);
      for (int i = 1; i < (1 << n); i++) {
        int cnt = __builtin_popcount(i);
        if (cnt & (cnt - 1)) continue;
        if (cnt == 1) {
          dp[i] = i;
          continue;
        }
        for (int j = i; j; j = (j - 1) & i) {
          if (__builtin_popcount(j) == cnt / 2){
            for (int p1 = 0; p1 < n; p1++)
              for (int p2 = 0; p2 < n; p2++) {
                if ((dp[j] & (1<<p1)) && (dp[i ^ j] & (1<<p2))) {
                  int p = w[p1][p2] ? p1 : p2;
                  dp[i] |= (1<<p);
                  ansl[p] = min(ansl[p], n / (2  * cnt) + 1);
                  ansr[p1 + p2 - p] = max(ansr[p1 + p2 - p], n / (cnt) + 1);
                } 
              }               
          }
        }
      }

      for (int i = 0; i < n; i++) {
        printf("%d %d\n", ansl[i], ansr[i]);
      }
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

  vector<Solver *> solvers(_testNum);

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
