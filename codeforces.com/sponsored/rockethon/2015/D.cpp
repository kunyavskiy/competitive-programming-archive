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

#define TASKNAME "D"

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

void error(){
  puts("IMPOSSIBLE");
  exit(0);
}

struct rest {
  int l, r;
  int ty;
  bool operator<(const rest& a){
    return l < a.l;
  }
};

const int MAXN = 1100000;

rest rs[1100000];
int firstR[MAXN];
int lastL[MAXN];
int lastAll[MAXN];
vector<int> ans;

void solve(int l, int r, int cl, int cr){
 // eprintf("[%d, %d) [%d, %d)", l, r, cl, cr);
  if (l == r) return;
  if (l == r - 1){
    ans.pb(l);
    return;
  }
  int lastL = l;
  //int i;
  /*for (i = cl; i < cr; i++) {
  //  eprintf("%d %d %d\n", rs[i].l, rs[i].r, rs[i].ty);
    if (rs[i].l == l && rs[i].ty == 1)
      continue;
    else if (rs[i].l <= lastL)
      lastL = max(lastL, rs[i].r);
    else
      break;
  }
  eprintf("l =%d, lastL = %d[%d]; i = %d;\n", l, lastL, ::lastL[l], i);
  assert(lastL == ::lastL[l]);*/
  if (firstR[l] <= ::lastL[l])
    error();
  //while (cl < cr && rs[cl].l == l) cl++;
  solve(l+1, lastL+1, cl, cr);
  ans.pb(l);
  solve(lastL+1, r, cl, cr);
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int n, c;
  scanf("%d%d",&n,&c);
  for (int i = 0; i < c; i++) {
    scanf("%d%d",&rs[i].l, &rs[i].r);
    --rs[i].l, --rs[i].r;
    if (rs[i].l >= rs[i].r){
      error();
    }
    char buf[10];
    scanf("%s", buf);
    if (!strcmp(buf, "LEFT"))
      rs[i].ty = 0;
    else
      rs[i].ty = 1;
  }
  sort(rs, rs + c);
  for (int i = 0; i < n; i++)
    firstR[i] = 1e9;
  for (int i = 0; i < c; i++)
    if (rs[i].ty == 1)
      firstR[rs[i].l] = min(firstR[rs[i].l], rs[i].r);
  vector<int> v;
  for (int i = c - 1; i >= 0; i--){
    int lf = rs[i].l;
    lastAll[lf] = max(lastAll[lf], rs[i].r);
    while (!v.empty() && v.back() <= lastAll[lf]){
      lastAll[lf] = max(lastAll[lf], lastAll[v.back()]);
      v.pop_back();
    }
    v.push_back(lf);
  }
  for (int i = 0; i < n; i++)
    if (lastAll[i] == 0)
      lastAll[i] = i;
  eprintf("%d %d %d %d\n", lastAll[0], lastAll[1], lastAll[2], lastAll[3]);
  v.clear();
  int ptr = c-1;
  for (int i = n - 1; i >= 0; i--){
    int maxL = i;
    while (ptr != -1 && rs[ptr].l == i){
      if (rs[ptr].ty == 0)
        maxL = max(maxL, rs[ptr].r);
      ptr--;
    }
    eprintf("%d %d\n", i, maxL);
    lastL[i] = i;
    while (!v.empty() && v.back() <= maxL) {
      lastL[i] = max(lastL[i], lastAll[v.back()]);
      v.pop_back();
    }
    v.pb(i);
  }
  eprintf("%d %d %d %d\n", lastL[0], lastL[1], lastL[2], lastL[3]);
  solve(0, n, 0, c);      
  for (int i = 0; i < (int)ans.size(); i++)
    printf("%d ", ans[i] + 1);
  printf("\n");
  return 0;
}