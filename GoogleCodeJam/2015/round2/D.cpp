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

#define TASKNAME "D"
#define TASKMOD "small"

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

class Solver : public AbstractSolver{
public:
Solver(int _testId) : AbstractSolver(_testId) {};

int n, m;
vector<vector<int>> a;
set<vector< vector<int> >> ans;

void canon(vector<vector<int>> v){
  auto best = v;
  for (int i = 0; i < (int)v[0].size(); i++){
    for (auto &x : v)
      rotate(x.begin(), x.begin()+1, x.end());
    best = min(best, v);
  }
  ans.insert(best);
}

bool check(int x, int y){
  int total = 0;
  if (x != 0   && a[x-1][y] == a[x][y]) ++total;
  if (x != n-1 && a[x+1][y] == a[x][y]) ++total;
  if (a[x][(y+m-1) % m] == a[x][y]) ++total;
  if (a[x][(y+1) % m] == a[x][y]) ++total;
  return total == a[x][y];
}

void go(int x, int y){
  if (y == m) {
    go(x+1, 0);
    return;
  }
  if (x == n){
    canon(a);
    return;
  }
  for (int i = 1; i <= 3; i++){
    a[x][y] = i;
    if (x && !check(x-1, y)) continue;
    if (x == n-1 && y > 1 && !check(x, y-1)) continue;
    if (x == n-1 && y == m-1 && !check(x, 0)) continue;
    if (x == n-1 && y == m-1 && !check(x, y)) continue;
    go(x, y+1);
  }
}

void read(){
  scanf("%d %d",&n,&m);
}
void solve(){
  a = vector<vector<int>>(n, vector<int>(m, 0));
  go(0,0);
  printf("%d\n", (int)ans.size());
  for (auto x : ans){
    for (auto v : x) {
      for (auto c : v)
        printf("%d", c);
      printf("\n");
    }
    printf("=====");
  }
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
