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
#pragma omp critical 
    {
      _solved++;
      if ((_solved - 1) * 100 / _testNum != _solved * 100 / _testNum || _solved <= 20 || _testNum - _solved <= 20) 
	TIMESTAMPf("%d%% of tests solved (%d/%d, %d more)", _solved * 100 / _testNum, _solved, _testNum, _testNum - _solved);
    }
  }
};

class MaxFlow {
  struct edge {
    int to;
    int c;
    int next;
  };
  vector<edge> es;
  vector<int> head;
  vector<bool> used;
  int n;
public:
  MaxFlow(int n):head(n, -1), n(n){};
  void addEdge(int a, int b, int c1, int c2){
    edge from = {b, c1, head[a]};
    edge to = {a, c2, head[b]};
    es.push_back(from);
    es.push_back(to);
    head[a] = (int) es.size() - 2;
    head[b] = (int) es.size() - 1;
  }

  int dfs(int v, int t){
    if (used[v]) return 0;
    if (v == t) return 1;
    used[v] = 1;
    for (int id = head[v]; id != -1; id = es[id].next){
      if (es[id].c && dfs(es[id].to, t) == 1){
        es[id].c--;
        es[id ^1].c++;
        return 1;
      }
    }
    return 0;
  }

  int flow(int s, int t){
    int ans = 0;
    while (true) {
      used = vector<bool>(n, 0);
      if (!dfs(s, t))
        break;
      ans++;
    }
    return ans;
  }
};


void PreCalc(){
}

class Solver : public AbstractSolver{
public:
Solver(int _testId) : AbstractSolver(_testId) {};

vector<vector<int>> ids;
map<string, int> id;

void read(){
  int n;
  static char buf[200000];
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &n);
  ids = vector<vector<int>>(n);
  for (int i = 0; i < n; i++){
    fgets(buf, sizeof buf, stdin);
    stringstream str(buf);
    while (str >> buf) {
      int bid = -1;
      if (id.count(buf)) {
        bid = id[buf];
      } else {
        bid = id.size();
        id[buf] = bid;
      }
      ids[i].push_back(bid);
    }
  }
}

void solve(){
  MaxFlow flow(2*id.size() + 2);
  for (int id : ids[0])
    flow.addEdge(0, id*2+2, 1e9, 0);
  for (int id : ids[1])
    flow.addEdge(id*2+3, 1, 1e9, 0);
  for (int i = 0; i < (int)id.size(); i++)
    flow.addEdge(i*2+2, i*2+3, 1, 0);

  for (int i = 2; i < (int)ids.size(); i++)
    for (int j = 0; j < (int)ids[i].size(); j++)
      for (int k = j+1; k < (int)ids[i].size(); k++){
        flow.addEdge(2*ids[i][j]+3, 2*ids[i][k]+2, 1, 0);
        flow.addEdge(2*ids[i][k]+3, 2*ids[i][j]+2, 1, 0);
      }

  int ans = flow.flow(0, 1);
  printf("%d\n", ans);
}

};

int main(){
  //freopen(TASKNAME "-" TASKMOD".in","r",stdin);
  //freopen(TASKNAME "-" TASKMOD".out","w",stdout);
	
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
