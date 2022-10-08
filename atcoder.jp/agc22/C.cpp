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

const int N = 51;

bool can(ll ans, const vector<int>& a, const vector<int> &b) {
  vector<vector<int>> g(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    g[i][i] = 1;
    for (int j = 1; j < N; j++) {
      if (ans & (1LL << j)) {
        g[i][i % j] = 1;
      }
    }
  }

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        g[i][j] |= g[i][k] & g[k][j];
      }
    }
  }

  for (int i = 0; i < (int)a.size(); i++) {
    if (!g[a[i]][b[i]]) {
      return false;
    }
  }
  return true;
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }

  ll ans = (1LL << N) - 1;

  if (!can(ans, a, b)) {
    printf("-1\n");
    return 0;
  }

  for (int i = N - 1; i >= 0; i--) {
    if (can(ans - (1LL << i), a, b)) {
      ans -= 1LL << i;
    }
  }

  printf("%lld\n", ans);

  return 0;
}
