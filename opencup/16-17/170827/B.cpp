#include <iostream>
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

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

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

#define TEST

#ifdef TEST
vector<int> correct;
#endif

int queries;
int r, d;

bool query(const vector<int> &v) {
  ++queries;
  assert(queries <= 100 * d);
#ifdef TEST
  static vector<int> last;
  if (last.empty()) {
    last = v;
    return false;
  }
  ll res = 0, lres = 0;
  for (int i = 0; i < (int)v.size(); i++) {
    assert(0 <= v[i] && v[i] <= r);
    res += abs(v[i] - correct[i]);
    lres += abs(last[i] - correct[i]);
  }
  last = v;
  return res < lres;
#else
  printf("?");
  for (int x : v) {
    printf(" %d", x);
  }
  printf("\n");
  fflush(stdout);
  char buff[200];
  scanf("%s", buff);
  return !strcmp(buff, "hotter");
#endif
}

int main() {
#ifdef TEST
  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
#endif

  scanf("%d%d", &d, &r);

#ifdef TEST
  correct.resize(d);
  for (int i = 0; i < d; i++) {
    scanf("%d", &correct[i]);
  }
#endif

  vector<int> ans(d);

  for (int i = 0; i < d; i++) {
    ans[i] = 0;
    query(ans);
    ans[i] = 1;
    if (!query(ans)) {
      ans[i] = 0;
      continue;
    }
    int lf = 0;
    int rg = r;
    while (rg - lf > 1) {
      int m = (lf + rg) / 2;
      ans[i] = m;
      query(ans);
      ans[i] = m + 1;
      if (query(ans)) {
        lf = m;
      } else {
        rg = m;
      }
    }
    ans[i] = rg;
  }

  printf("!");
  for (int x : ans) {
    printf(" %d", x);
  }
  printf("\n");

  return 0;
}
