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

const int MAXN = 200000;

vector<int> g[MAXN];
vector<bool> used;

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < n; i++) {
      g[i].clear();
    }
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d",&a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }

    used = vector<bool>(n);
    used[0] = 1;

    vector<int> p1, p2;
    p1.push_back(0);
    for (int i = 0; i < 2; i++) {
      int v = 0;
      while (true) {
        bool any = false;
        for (int u : g[v]) {
          if (!used[u]) {
            any = true;
            p1.push_back(u);
            v = u;
            used[v] = true;
            break;
          }
        }
        if (!any) break;
      }
      p1.swap(p2);
    }

    reverse(p2.begin(), p2.end());
    p2.insert(p2.end(), p1.begin(), p1.end());

    printf("%d\n", (int) p2.size());
    for (int i : p2) {
      printf("%d ", i + 1);
    }
    printf("\n");
  }
  return 0;
}
