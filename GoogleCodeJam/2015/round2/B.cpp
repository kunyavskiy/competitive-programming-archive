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

class Solver : public AbstractSolver{
public:
Solver(int _testId) : AbstractSolver(_testId) {}

vector<int> r;
vector<int> c;
int v;

int readDouble(){
  int a, b;
  assert(scanf("%d.%d",&a, &b) == 2);
  return a * 10000 + b;
}

void read(){
  int n;
  scanf("%d",&n);
  int x;
  v = readDouble();
  x = readDouble();
  r.resize(n);
  c.resize(n);
  for (int i = 0; i < n; i++){
    r[i] = readDouble();
    c[i] = readDouble() - x;
  }
}
int sgn(long long a){
  return (a > 0) - (a < 0);
}
void solve_old(){
  if (r.size() == 1){
    if (c[0] == 0){
      printf("%.10f\n", v * 1.0 / r[0]);
    } else {
      printf("IMPOSSIBLE\n");
    }
    return;
  }
  assert(r.size() == 2);
  long long A = r[0];
  long long B = r[1];
  long long C = r[0] * 1LL * c[0];
  long long D = r[1] * 1LL * c[1];
  assert(0 < A && A <= 1e6);
  assert(0 < B && B <= 1e6);
  assert(-1e12 <= C && C <= 1e12);
  assert(-1e12 <= D && D <= 1e12);
  if (C == 0 && D == 0) {
    printf("%.10f\n", v * 1.0 / (A + B));
    return;
  }
  if (C == 0) {
    swap(A, B);
    swap(C, D);
  }
  assert(C);
  long long det = A * D - B * C;
  if (sgn(C) * sgn(det) >= 0) {
    printf("IMPOSSIBLE\n");
    return;
  }
  if (sgn(D) * sgn(C) > 0) {
    printf("IMPOSSIBLE\n");
    return;
  }
  //fprintf(stderr, "det = %lld\n", det);
  double x2 = v * 1.0 / -det * C;
  double x1 = -D *1.0/ C * x2 ;
  //printf("%.10f %.10f\n", x1, x2);
  assert(x1 >= 0);
  assert(x2 >= 0);
  //fprintf(stderr, "%.10f %.10f %lld %lld %lld %lld %d\n", A*x1 +B*x2 - v, C*x1+D*x2, A, B, C, D, v);
  //assert(fabs(A*x1 +B*x2 - v) < 1e-5);
  //assert(fabs(C*x1 +D*x2) < 1e-3);
  printf("%.10f\n", max(x1, x2));
}

double calc(vector<pair<double, double>> v, double total){
  double res = 0;
  for (auto x : v){
    double c = min(total, x.second);
    total -= c;
    res += x.first * c;
  }
  return total > 0 ? 1e9 : res;
}

bool check(double t){
  int n = r.size();
  vector<pair<double, double> > res(n);
  for (int i = 0; i < n; i++){
    res[i] = mp(c[i], min(v*1.0, r[i]*t));
  }
  sort(res.begin(), res.end());
  double min = calc(res, v);
  reverse(res.begin(), res.end());
  double max = calc(res, v);
  return min <= 0 && max >= 0;
}

void solve(){
  double l = 0;
  double r = 1e9;
  if (!check(r)){
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int i = 0; i < 100; i++){
    double m = (l+r)/2;
    if (check((l+r)/2))
      r = m;
    else
      l = m;
  }
  printf("%.10f\n", (l+r)/2);
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
 
  //#pragma omp parallel for
  for (int i = 0; i < _testNum; i++) {
    solvers[i]->run();
  }

  for (int i = 0; i < _testNum; i++) {
    solvers[i]->write();
  }

  TIMESTAMP(end);
  return 0;
}
