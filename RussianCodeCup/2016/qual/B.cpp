#define __USE_MINGW_ANSI_STDIO 0
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

#define TASKNAME "B"

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
  int n, h;
  scanf("%d%d",&n,&h);
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    scanf("%d",&a[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d",&b[i]);
  }

  int r = 0;
  int tot = 0;
  int cnt = 0;
  int ans = 0;
  if (b[0] == 0) {
    b[0] = 1;
    ans++;
  }
  if (b[n-1] == 0) {
    b[n-1] = 1;
    ans++;
  }
  for (int i = 0; i < n; i++) {
    while (r < n && tot < h) {
      tot += a[r];
      cnt += b[r];
      r++;
    }
    if (cnt == 0) {
      ans++;
      cnt++;
      b[r-1] = 1;
    }
    tot -= a[i];
    cnt -= b[i];
  }
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int t;
  scanf("%d",&t);
  while (t-->0) solve();
  return 0;
}
