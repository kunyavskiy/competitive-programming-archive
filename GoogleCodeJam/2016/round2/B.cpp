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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;


int _solved, _testNum;

class AbstractSolver {
  char* _ob;
  int _ob_pos;
  const int _buffer_size = 16 * (1<<20);
public:
  int _testId;
  AbstractSolver(int _testId) : _testId(_testId) {
      _ob = (char*)malloc(_buffer_size + 10);
      _ob_pos = 0;
      printf("Case #%d: ", _testId);
  }
  __attribute__((format(printf, 2, 3)))
  void printf (const char *format, ...) {
    va_list ap;
    va_start (ap, format);
    _ob_pos += vsnprintf (_ob + _ob_pos, _buffer_size - _ob_pos, format, ap);
    va_end (ap);
    assert(_ob_pos < _buffer_size - 10);
  }

  virtual void write(){
    _ob[_ob_pos] = 0;
    ::printf("%s", _ob);
  }

  virtual void solve() = 0;;
  virtual void read() = 0;

  void run(){
    solve();
#pragma omp critical 
    {
      _solved++;
      if ((_solved - 1) * 100 / _testNum != _solved * 100 / _testNum || _solved <= 20 || _testNum - _solved <= 20) 
	TIMESTAMPf("%d%% of tests solved (%d/%d, %d more)", _solved * 100 / _testNum, _solved, _testNum, _testNum - _solved);
    }
  }
};


void PreCalc(){
}

class Solver : public AbstractSolver {
public:
  Solver(int _testId) : AbstractSolver(_testId) { }

  int k;
  vector<double> p;

  void read() {
    int n;
    scanf("%d%d",&n,&k);
    p.resize(n);
    for (double& x : p) {
      scanf("%lf",&x);
    }
  }

  double dp[205][205];

  double solve_one(vector<double> p) {
    int n = p.size();
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        dp[i+1][j+1] += dp[i][j] * p[i];
        dp[i+1][j] += dp[i][j] * (1 - p[i]);
      }
    }
    return dp[n][n/2];
  }

  double go(vector<double> v, int pos, int k) {
    if ((int)v.size() == k) return solve_one(v);
    if (pos == (int)p.size()) return 0.0;
    double ans = go(v, pos+1, k);
    v.push_back(p[pos]);
    ans = max(ans, go(v, pos+1, k));
    return ans;
  }

  double solve2() {
    int n = p.size();
    double ans = 0.0;
    sort(p.begin(), p.end());
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n && j <= i + k; j++) {
        int sec = k - (j - i);
        for (int t = j; t + sec <= n; t++) {
          if (t + sec != n) {
            continue;
          }
          vector<double> x;
          x.insert(x.end(), p.begin() + i, p.begin() + j);
          x.insert(x.end(), p.begin() + t, p.begin() + t + sec);
          assert((int)x.size() == k);
          ans = max(ans, solve_one(x));
        }
      }
    }
    return ans;
  }

  void solve() {
    double nans = solve2();
    //double ans = go(vector<double>(), 0, k);
    //assert(fabs(ans - nans) < 1e-8);
    printf("%.10f\n", nans);
  }

};

int main(){
  freopen(TASKNAME "-" TASKMOD".in","r",stdin);
  freopen(TASKNAME "-" TASKMOD".out","w",stdout);
	
  PreCalc();
  TIMESTAMP(PreCalc);	

  char buf[1000];
  fgets(buf, sizeof buf, stdin);
  sscanf(buf,"%d",&_testNum);

  vector<Solver*> solvers(_testNum);

  for (int i = 0; i < _testNum; i++) {
    solvers[i] = new Solver(i+1);
    solvers[i]->read();
  }
 
  #pragma omp parallel for 
  for (int i = 0; i < _testNum; i++) {
    solvers[i]->run();
  }

  for (int i = 0; i < _testNum; i++) {
    solvers[i]->write();
  }

  TIMESTAMP(end);
  return 0;
}
