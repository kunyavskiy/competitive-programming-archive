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

#define TASKNAME "A"

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

    vector<int> v;

    void read() {
      int n;
      scanf("%d",&n);
      v.resize(n);
      for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
      }
    }

    bool check2(int a, int b) {
      return a < b && b <= a + 30;
    }

    bool check3(int a, int b, int c) {
      vector<int> v = {a, b, c};
      if (!is_sorted(v.begin(), v.end())) return false;
      if (unique(v.begin(), v.end()) != v.end()) return false;
      if (v[2] - v[0] > 30) return false;
      if (v[1] - v[0] > 20) return false;
      if (v[2] - v[1] > 20) return false;
      if (v[2] - v[1] > 10 && v[1] - v[0] > 10) return false;
      return true;
    }

    bool check4(int a, int b, int c, int d) {
      vector<int> v = {a, b, c, d};
      if (!is_sorted(v.begin(), v.end())) return false;
      if (unique(v.begin(), v.end()) != v.end()) return false;
      if (v[1] > v[0] + 10) return false;
      if (v[2] > v[1] + 10) return false;
      if (v[3] > v[2] + 10) return false;
      return true;
    }

    void solve() {
      vector<int> dp(v.size() + 1, (int) 1e9);
      dp[0] = 0;
      for (int i = 0; i < (int)v.size(); i++) {
        dp[i+1] = min(dp[i+1], dp[i] + 3);
        if (i + 1 < (int)v.size() && check2(v[i], v[i+1])) dp[i+2] = min(dp[i+2], dp[i] + 2);
        if (i + 2 < (int)v.size() && check3(v[i], v[i+1], v[i+2])) dp[i+3] = min(dp[i+3], dp[i] + 1);
        if (i + 3 < (int)v.size() && check4(v[i], v[i+1], v[i+2], v[i+3])) dp[i+4] = min(dp[i+4], dp[i] + 0);
      }
      printf("%d\n", dp[v.size()]);
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
