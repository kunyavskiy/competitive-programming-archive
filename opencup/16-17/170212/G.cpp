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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "G"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

void doAll(int n, vector <int> & a,
           vector <int> & b,
           vector <int> & c1,
           vector <int> & c2,
           vector <int> & c3) {
  for (int i = 1; i < n; ++i) {
    c1[i] = min(a[i], b[i] - c2[i - 1]);
    if (i == n - 1) {
      c2[i] = min(a[i] - c1[i], b[0] - c1[0]);
    } else {
      c2[i] = min(a[i] - c1[i], b[i + 1]);
    }
    c3[i] = a[i] - c1[i] - c2[i];
  }

  for (int i = 0; i < n; ++i) {
    eprintf("%d %d %d %d %d\n", a[i], b[i], c1[i], c2[i], c3[i]);
  }
  eprintf("\n");
}


bool solve() {
  int n;
  if (scanf("%d", &n) != 1) {
    return 0;
  }

  vector <int> a(n);
  vector <int> b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
  }
  vector <int> c1(n), c2(n), c3(n);
  c1[0] = min(a[0], b[0]);
  c2[0] = min(a[0] - c1[0], b[1]);
  c3[0] = a[0] - c1[0] - c2[0];
  doAll(n, a, b, c1, c2, c3);

  int x = min(c3[n - 1], c1[0]);
  c3[n - 1] -= x;
  c2[n - 1] += x;
  c1[0] -= x;
  c2[0] = min(a[0] - c1[0], b[1]);
  c3[0] = a[0] - c1[0] - c2[0];
  doAll(n, a, b, c1, c2, c3);

  ll res = 0;
  for (int i = 0; i < n; ++i) {
    res += c1[i] + c2[i];
  }
  printf("%lld\n", res);

  return true;
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

  while (solve()) {
  }

  return 0;
}
