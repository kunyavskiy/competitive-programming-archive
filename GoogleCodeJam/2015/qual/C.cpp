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

#define TASKNAME ""
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

  virtual void solve() = 0;

  void run(){
    solve();
#pragma omp critical 
    {
      _solved++;
      if ((_solved - 1) * 100 / _testNum != _solved * 100 / _testNum) 
	TIMESTAMPf("%d%% of tests solved", _solved * 100 / _testNum);
    }
  }
};


void PreCalc(){
}


int mult(int a, int b) {
  int res = a ^ b;
  if ((a & 3) == 0 || (b & 3) == 0)
      return res;
  a = (a & 3) - 1;
  b = (b & 3) - 1;
  if (a == b || (a + 2) % 3 == b)
      return res ^ 4;
  return res;
}


class Solver : public AbstractSolver{
public:
Solver(int _testId) : AbstractSolver(_testId) {}

char s[10000 * 100 + 10];

void read(){
    long long X;
    int l;
    scanf("%d%lld%s", &l, &X, s);
    X -= 4 * max(0LL, (X - 18) / 4);
    assert(X <= 22);
    for (int i = l; i < l * X; i++)
	s[i] = s[i-l];
}

void solve(){
   int all = 0;
   for (int i = 0; s[i]; i++)
       all = mult(all, s[i] - 'i' + 1);
   if (all != 4){
      printf("NO\n");
      return;
   }
   int n = strlen(s);
   int cur = 0;
   int lf, rg;
   for (lf = 0; lf < n && cur != 1; lf++){
       cur = mult(cur, s[lf] - 'i' + 1);
   }
   cur = 0;
   for (rg = n - 1; rg >= 0 && cur != 3; rg--){
       cur = mult(s[rg] - 'i' + 1, cur);
   }
   printf("%s\n", lf <= rg ? "YES" : "NO");
}

};

int main(){
	
  PreCalc();
  TIMESTAMP(PreCalc);	

  char buf[1000];
  fgets(buf, sizeof stdin, stdin);
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
