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

vector<int> get_input(int n) {
  vector<int> a(n + 1);
  int x = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    x ^= a[i];
  }
  a[n] = x;
  return a;
}

vector<vector<int>> g;
vector<bool> used;

void dfs(int v) {
  if (used[v]) return;
  used[v] = true;
  for (int u : g[v])
    dfs(u);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a = get_input(n);
    vector<int> b = get_input(n);
    n += 1;

    vector<int> as = a, bs = b;
    sort(as.begin(), as.end());
    sort(bs.begin(), bs.end());
    if (as != bs) {
      printf("-1\n");
      continue;
    }

    as.erase(unique(as.begin(), as.end()), as.end());
    for (int &x : a) {
      x = (int) (lower_bound(as.begin(), as.end(), x) - as.begin());
    }
    for (int &x : b) {
      x = (int) (lower_bound(as.begin(), as.end(), x) - as.begin());
    }

    g = vector<vector<int>>(as.size());
    used = vector<bool>(as.size());

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] != b[i]) {
        g[a[i]].push_back(b[i]);
        g[b[i]].push_back(a[i]);
        ans++;
      }
    }

    for (int i = 0; i < (int)as.size(); i++) {
      if (used[i]) continue;
      if (g[i].empty()) continue;
      ans++;
      dfs(i);
    }

    if (!g[a[n-1]].empty()) {
      ans -= 2;
      if (a[n-1] == b[n-1]) {
        ans += 1;
      }
    }


    printf("%d\n", ans);
  }

  return 0;
}
