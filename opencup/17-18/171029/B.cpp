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

const int MAXN = 510000;

char s[MAXN];
set<int> open, close;

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  scanf("%s", s);
  for (int i = 0; s[i]; i++) {
    if (s[i] == '(') {
      open.insert(i);
    } else {
      close.insert(i);
    }
  }

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l;
    int ans = 0;
    while (true) {
      auto cit_l = close.lower_bound(r);
      if (cit_l == close.begin()) break;
      --cit_l;
      auto oit = open.lower_bound(*cit_l);
      if (oit == open.begin()) break;
      --oit;
      if (*oit < l) break;
      auto cit = close.lower_bound(*oit);
      assert(cit != close.end() && *cit < r);
      ans += 2;
      open.erase(oit);
      close.erase(cit);
    }
    printf("%d\n", ans);
  }


  return 0;
}
