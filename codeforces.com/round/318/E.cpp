//#include <iostream>

#pragma GCC optimize "-O3"
#include <fstream>
#include <cassert>

#ifndef __LP64__
#error fuck
#endif

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

#define TASKNAME "E"

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

const int MAXN = 100100;
ll dp[MAXN];
int a[MAXN];

int my_rand(){
  return (rand() << 15) + rand();
}

int main(){
  #ifdef LOCAL
  assert(freopen(TASKNAME".in","r",stdin));
  assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int n;
  n = 100000;
  /*scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }*/
  for (int i = 0; i < n; i++)
    a[i] = my_rand() % (int)2e7 - (int)1e7;


  for (int i = n - 1; i >= 0; i--) {
    ll add = 0;
    ll* dp = ::dp;
    ll* dp_end = ::dp + i + 1;
    for (; dp != dp_end; dp++) {
      *dp = max(*dp, (add += a[i]) + dp[1]);
    }
  }

  printf("%lld\n", dp[0]);
  return 0;
}
