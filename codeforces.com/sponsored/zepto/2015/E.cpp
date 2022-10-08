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

#define TASKNAME "E"
#define next next_ololo

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

const int MAXN = 1100000;
int n;
int a[MAXN*2];
int next[MAXN*2];

int solve(long long b){
  long long sum = 0;
  int j = 0;
  for (int i = 0; i < 2*n; i++){
    while (j < 2*n && sum + a[j] <= b) {
      sum += a[j];
      j++;
    }
    next[i] = j;
    sum -= a[i];
  }
  int best = 0;
  int bestlen = 2*n;
  for (int i = 0; i < n; i = next[i]) {
    if (next[i] - i < bestlen) {
      best = i;
      bestlen = next[i] - i;
    }
  }


  int res = 2*n;
  for (int start = best; start <= next[best]; start++){
    int cnt = 0;
    for (int i = start; i < start + n; i = next[i]) {
      cnt++;
    }
    res = min(res, cnt);
  }
  return res;
}



int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int q;
  scanf("%d%d",&n,&q);
  for (int i = 0; i < n; i++){
    scanf("%d",&a[i]);
    a[i+n] = a[i];
  }

  for (int i = 0; i < q; i++){
    long long b;
    scanf(LLD,&b);
    printf("%d\n", solve(b));
  }
      
  return 0;
}
