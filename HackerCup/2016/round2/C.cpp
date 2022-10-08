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

#define TASKNAME "C"

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

    vector<pair<int, int>> s;
    int ans;

    void read() {
      int n;
      scanf("%d", &n);
      s.resize(n);
      for (auto &x : s) {
        scanf("%d%d", &x.first, &x.second);
      }
    }

    const int MOD = 1000000007;

    void add(int &a, int b) {
      if ((a += b) >= MOD) a -= MOD;
    }

    int mult(int a, int b) {
      return (a * 1LL * b) % MOD;
    }

    void to_ans(const vector<int> &v) {
      int sum2 = 0;
      int sum = 0;
      for (int x : v) {
        add(sum2, mult(x, x));
        add(sum, x);
      }
      add(ans, mult(v.size(), sum2));
      add(ans, MOD - mult(sum, sum));
    }

    void solve() {
      sort(s.begin(), s.end());
      vector<pair<int, vector<int>>> st;
      ans = 0;
      for (const auto &x : s) {
        while (st.size() && st.back().first < x.second) {
          to_ans(st.back().second);
          st.pop_back();
        }
        if (st.size() && st.back().first == x.second) {
          st.back().second.push_back(x.first);
        } else {
          st.push_back(mp(x.second, vector<int>(1, x.first)));
        }
      }
      while (!st.empty()) {
        to_ans(st.back().second);
        st.pop_back();
      }
      printf("%d\n", ans % MOD);
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
