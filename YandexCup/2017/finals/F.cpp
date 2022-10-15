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

const int MAXN = 300100;

double x[MAXN];
vector<int> g[MAXN];

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &x[i]);
  }

  double lam = 0;

  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
    lam += min(x[u], x[v]);
  }

  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = i;
  }

  sort(v.begin(), v.end(), [](int a, int b) -> bool { return x[a] > x[b];});

  vector<int> used(n);
  int cnt = 0;

  for (int i = 0; i < n; i++) {
    used[v[i]] = 1;
    for (int u : g[v[i]]) {
      if (used[u]) cnt++;
    }
    if (cnt >= (i + 1) * lam - (1e-9)) {
      printf("%d\n", i + 1);
      sort(v.begin(), v.begin() + i + 1);
      for (int j = 0; j <= i; j++) {
        printf("%d ", v[j] + 1);
      }
      printf("\n");
      return 0;
    }
  }


  return 0;
}
