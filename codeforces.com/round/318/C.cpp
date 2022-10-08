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

#define TASKNAME "C"

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


const int MAXN = 110000;
vector<int> g[MAXN];

enum Tp {FAIL, NONE, ONE_LINE_ONE_SIDE, ONE_LINE_TWO_SIDE, TWO_LINES_ONE_SIDE, TWO_LINES_TWO_SIDE, TP_LAST};

Tp dfs(int v, int p = -1) {
  int count[TP_LAST];
  memset(count, 0, sizeof(count));
  int total = 0;
  for (int to : g[v]) {
    if (to == p)
      continue;
    ++total;
    Tp res = dfs(to, v);
    eprintf("dfs(%d) = %d\n", to, res);
    count[res]++;
  }
  if (count[FAIL] > 0) return FAIL;
  if (!total) return NONE;
  int one_lines = count[NONE] + count[ONE_LINE_ONE_SIDE];
  if (count[TWO_LINES_TWO_SIDE]) {
    if (one_lines <= 2) return TWO_LINES_TWO_SIDE;
    return FAIL;
  }
  if (one_lines == total && one_lines == 1) return ONE_LINE_ONE_SIDE;
  if (one_lines == total && one_lines == 2) return ONE_LINE_TWO_SIDE;
  int one_lines2 = count[NONE] + count[ONE_LINE_ONE_SIDE] + count[ONE_LINE_TWO_SIDE];
  if (one_lines2 < total - 2) return FAIL;
  if (one_lines2 >= total - 1 && count[TWO_LINES_ONE_SIDE] <= 1) return TWO_LINES_ONE_SIDE;
  if (one_lines2 == total - 2 && count[TWO_LINES_ONE_SIDE] == 2) return TWO_LINES_TWO_SIDE;
  assert (0);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n-1; i++) {
    int a, b;
    scanf("%d%d",&a,&b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  if (dfs(0) != FAIL)
    printf("Yes\n");
  else
    printf("No\n");

      
  return 0;
}
