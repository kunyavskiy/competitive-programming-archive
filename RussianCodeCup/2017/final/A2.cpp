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
    vector<int> v(n);
    for (int &x: v) {
      scanf("%d", &x);
    }
    sort(v.begin(), v.end());
    vector<int> vv;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        vv.push_back(v[j] - v[i]);
      }
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    vv.push_back(1e9);
    for (int i = 1;; i++) {
      if (i * (n - 1) + 1 > 1000000) {
        assert(0);
        printf("NO\n");
        break;
      }
      if (vv[i - 1] != i) {
        printf("YES\n");
        vector<int> u;
        for (int j = 0; j < n; j++) {
          u.push_back(i * j + 1);
          printf("%d ", u.back());
        }
        vector<int> uv;
        for (int x : u) {
          for (int y : v) {
            uv.push_back(x + y);
          }
        }
        sort(uv.begin(), uv.end());
        assert(unique(uv.begin(), uv.end()) == uv.end());
        printf("\n");
        break;
      }
    }
  }
  return 0;
}
