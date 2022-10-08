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

int a[500][500];

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &a[i][j]);
        a[i][j]--;
      }
    }
    for (int ans = 1; ; ans++) {
      vector<int> count(m);
      vector<int> ptr(n);
      for (int i = 0; i < n; i++) {
        count[a[i][0]]++;
      }
      while (true) {
        int id = max_element(count.begin(), count.end()) - count.begin();
        if (count[id] <= ans) break;
        count[id] = -1;
        for (int i = 0; i < n; i++) {
          if (count[a[i][ptr[i]]] != -1) continue;
          while (ptr[i] < m && count[a[i][ptr[i]]] == -1) {
            ptr[i]++;
          }
          if (ptr[i] < m) {
            count[a[i][ptr[i]]]++;
          }
        }
      }
      if (*max_element(count.begin(), count.end()) != -1) {
        printf("%d\n", ans);
        break;
      }
    }
  }

  return 0;
}
