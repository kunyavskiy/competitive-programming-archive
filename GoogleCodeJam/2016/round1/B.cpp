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
#define TASKMOD "dbg"

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
//#pragma omp critical 
    {
      _solved++;
      if ((_solved - 1) * 100 / _testNum != _solved * 100 / _testNum || _solved <= 20 || _testNum - _solved <= 20) 
	TIMESTAMPf("%d%% of tests solved (%d/%d, %d more)", _solved * 100 / _testNum, _solved, _testNum, _testNum - _solved);
    }
  }
};

bool cmp1(const pair<ll, ll> &a, const pair<ll, ll>& b) {
  ll value1 = a.first - a.second;
  ll value2 = b.first - b.second;
  if (value1 < 0) value1 *= -1;
  if (value2 < 0) value2 *= -1;
  eprintf("a.first = %lld, a.second = %lld, value1 = %lld\n", a.first, a.second, value1);
  if (value1 != value2)
    return value1 < value2;
  return a < b;
}

bool cmp2(const pair<ll, ll> &a, const pair<ll, ll>& b) {
  ll value1 = a.first - a.second;
  ll value2 = b.first - b.second;
  if (value1 != value2)
    return value1 > value2;
  return a < b;
}

bool cmp3(const pair<ll, ll> &a, const pair<ll, ll>& b) {
  ll value1 = a.second - a.first;
  ll value2 = b.second - b.first;
  if (value1 != value2)
    return value1 > value2;
  return a < b;
}


void PreCalc(){
}

class Solver : public AbstractSolver{
char s[20], t[20];
public:
Solver(int _testId) : AbstractSolver(_testId) {}

void read(){
  scanf("%s%s", s, t);
}
void solve(){
  ll deg10 = 1;
  int len = strlen(s);
  vector<pair<ll, ll>> vals;
  vals.push_back(make_pair(0LL,0LL));
  for (int i = len - 1; i >= 0; i--) {
    vector<pair<ll, ll>> nvals;
    for (auto x : vals) {
      for (int a = 0; a < 10; a++)
        for (int b = 0; b < 10; b++) {
          if (a == s[i] - '0' || s[i] == '?')
          if (b == t[i] - '0' || t[i] == '?') {
            nvals.push_back(make_pair(x.first + a * deg10, x.second + b * deg10));
            eprintf("%0*lld %0*lld\n", len - i, nvals.back().first, len - i, nvals.back().second);
          }
        }
    }
    vals.clear();
    vals.push_back(*min_element(nvals.begin(), nvals.end(), cmp1));
    vals.push_back(*min_element(nvals.begin(), nvals.end(), cmp2));
    vals.push_back(*min_element(nvals.begin(), nvals.end(), cmp3));

    for (auto x : nvals) {
      eprintf("cmp1(%lld:%lld,%lld:%lld) = %d\n", vals[0].first, vals[0].second, x.first, x.second, cmp1(vals[0], x));
    }

    eprintf("???\n");
    eprintf("%0*lld %0*lld\n", len - i, vals[0].first, len - i, vals[0].second);
    eprintf("%0*lld %0*lld\n", len - i, vals[1].first, len - i, vals[1].second);
    eprintf("%0*lld %0*lld\n", len - i, vals[2].first, len - i, vals[2].second);
    eprintf("=======\n");
    deg10 *= 10;
  }
  printf("%0*lld %0*lld\n", len, vals[0].first, len, vals[0].second);
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
 
//  #pragma omp parallel for 
  for (int i = 0; i < _testNum; i++) {
    solvers[i]->run();
  }

  for (int i = 0; i < _testNum; i++) {
    solvers[i]->write();
  }

  TIMESTAMP(end);
  return 0;
}
