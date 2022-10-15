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

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, q;
  scanf("%d%d", &n, &q);
  vector<ll> x(n);
  for (ll &a : x) {
    scanf("%lld", &a);
  }

  for (int i = 0; i < q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    set<pair<ll, int>> s;
    bool any = false;
    for (int j = l - 1; j < r && !any; j++) {
      auto it = s.insert({x[j], j}).first;
      if (s.size() < 3) continue;
      vector<int> v(5);
      if (it != s.begin()) it--;
      if (it != s.begin()) it--;
      auto a = *(it++);
      auto b = *(it++);
      auto c = *(it++);
      for (int k = 0; k < 3; k++) {
        if (a.first + b.first > c.first) {
          printf("%d %d %d\n", a.second + 1, b.second + 1, c.second + 1);
          any = true;
          break;
        }
        if (it == s.end()) break;
        a = b;
        b = c;
        c = *(it++);
      }
    }
    if (!any) {
      printf("-1\n");
    }
  }

  return 0;
}
