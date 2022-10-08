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

#define TASKNAME "A"

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

void solve() {
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  swap(b, c);
  if (abs(b - c) > 1) {
    printf("impossible\n");
    return;
  }
  if (b == 0 && c == 0 && a != 0 && d != 0) {
    printf("impossible\n");
    return;
  }
  char ans[200];
  int ptr = 0;
  char c1 = '1';
  char c0 = '0';
  if (b < c) {
    swap(b, c);
    swap(a, d);
    swap(c1, c0);
  }
  if (b == 0) {
    assert(c == 0);
    if (a) {
      for (int i = 0; i <= a; i++) {
        printf("0");
      }
    }
    if (d){
      for (int i = 0; i <= d; i++) {
        printf("1");
      }
    }
    printf("\n");
    return;
  }
  for (int i = 0; i < d; i++)
    ans[ptr++] = c1;
  for (int i = 0; i < b; i++) {
    ans[ptr++] = c1;
    ans[ptr++] = c0;
    if (i == 0) {
      for (int j = 0; j < a; j++) {
        ans[ptr++] = c0;
      }
    }
  }
  if (b == c) {
    ans[ptr++] = c1;
  }
  ans[ptr++] = 0;
  puts(ans);
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int t;
  scanf("%d",&t);
  while (t --> 0) {
    solve();
  }


  return 0;
}
