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

#define TASKNAME "A"
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

  int n, p, r, s;

  void read() {
    scanf("%d %d %d %d", &n, &r, &p, &s);
  }


  string solve(int n, int p, int r, int s) {
    if (n <= 1) {
      string res;
      if (p) res += "P";
      if (r) res += "R";
      if (s) res += "S";
      if ((int)res.size() != (1 << n)) return "";
      return res;
    }
    int count = (1 << (n - 2));
    if (p < count || r < count || s < count) return "";
    string in_res = solve(n - 2, r - count, s - count, p - count);
    string res = "";
    for (int i = 0; i < (int)in_res.size(); i++) {
      if (in_res[i] == 'P') res += "PRRS";
      if (in_res[i] == 'R') res += "PSRS";
      if (in_res[i] == 'S') res += "PSPR";
    }
    return res;
  }

  string normalize(string s) {
    if (s.size() == 1) return s;
    string a = string(s.begin(), s.begin() + s.size() / 2);
    string b = string(s.begin() + s.size() / 2, s.end());
    a = normalize(a);
    b = normalize(b);
    return min(a + b, b + a);
  }

  char cmp(char a, char b) {
    if (a > b) swap(a, b);
    if (a == 'P' && b == 'S') return 'S';
    if (a == 'P' && b == 'R') return 'P';
    if (a == 'R' && b == 'S') return 'R';
    assert(0);
  }

  bool check(string s) {
    while (s.size() != 1) {
      string ns = "";
      for (int i = 0; i < (int)s.size(); i += 2) {
        if (s[i] == s[i+1]) return false;
        ns += cmp(s[i], s[i+1]);
      }
      s = ns;
    }
    return true;
  }

  string solve2(int , int p, int r, int s) {
    string ans = "";
    string res = "";
    for (int i = 0; i < p; i++) res += "P";
    for (int i = 0; i < r; i++) res += "R";
    for (int i = 0; i < s; i++) res += "S";
    sort(res.begin(), res.end());

    do {
      if (check(res)) {
        if (ans == "" || ans > res)
          ans = res;
      }
    } while (next_permutation(res.begin(), res.end()));
    return ans;
  }

  void solve() {
    string res = solve(n, p, r, s);
    if (res != "") {
      res = normalize(res);
    }
    /*string res2 = solve2(n, p, r, s);
    if(res != res2) {
      eprintf("%d %d %d %d |%s| |%s|\n", n, p, r, s, res.c_str(), res2.c_str());
    }*/
    if (res == "")
      res = "IMPOSSIBLE";
    printf("%s\n", res.c_str());
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
