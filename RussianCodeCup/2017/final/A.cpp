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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%*d");
  int n;
  while (scanf("%d", &n) == 1) {
    eprintf("n = %d\n", n);
    vector<int> v(n);
    for (int &x: v) {
      scanf("%d", &x);
    }
    sort(v.begin(), v.end());
    vector<int> u;
    set<int> uv;
    for (int i = 1; i <= 1000000 && (int)u.size() < n; i++) {
      bool ok = true;
      for (int x : v) {
        if (uv.count(x + i)) {
          ok = false;
          break;
        }
      }
      if (ok) {
        u.push_back(i);
        for (int x : v) {
          uv.insert(x + i);
        }
      }
    }
    if ((int)u.size() < n) {
      printf("NO\n");
      assert(0);
    } else {
      printf("YES\n");
      for (int x : u) {
        printf("%d ", x);
      }
      printf("\n");
    }
  }
  return 0;
}
