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

#define TASKNAME "C"
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

class Solver : public AbstractSolver{
public:
Solver(int _testId) : AbstractSolver(_testId) {}

vector<vector<int>> g;
int n[2];
int k;
vector<int> mt;
vector<bool> used;

void read(){
  static char buf[2000];
  n[0] = n[1] = 0;
  scanf("%d", &k);
  map<string, int> names[2];
  for (int i = 0; i < k; i++) {
    int a[2];
    for (int j = 0; j < 2; j++) {
      scanf("%s", buf);
      if (!names[j].count(buf)) {
        names[j][buf] = n[j]++;
        if (j == 0) g.push_back(vector<int>());
      }
      a[j] = names[j][buf];
    }
    g[a[0]].push_back(a[1]);
  }
}

int dfs(int v) {
  if (used[v]) return false;
  used[v] = true;
  for (int u : g[v]) {
    if (mt[u] == -1 || dfs(mt[u])) {
      mt[u] = v;
      return true;
    }
  }
  return false;
}


void solve(){
  mt.resize(n[1], -1);

  k -= n[0] + n[1];
  for (int i = 0; i < n[0]; i++) {
    used = vector<bool>(n[0], false);
    k += dfs(i);
  }
  printf("%d\n", k);
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
