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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

  int n, th;
  scanf("%d%d", &n, &th);
  n += 2;
  vector<int> n0(n), n1(n);
  vector<int> used(n);
  vector<int> ans(n);

  auto dfs = [&](auto dfs, int v, int c, int w) -> void {
      if (used[v] == c) return;
      used[v] = c;
      ans[v] += w;
      dfs(dfs, n0[v], c, w);
      dfs(dfs, n1[v], c, w);
      dfs(dfs, n1[v], c, w);
  };
  for (int i = 2; i < n; i++) {
      int w;
      scanf("%*d %d %d %d", &n0[i], &n1[i], &w);
      dfs(dfs, i, i, w);
  }
  int cnt = 0;
  for (int i = 2; i < n; i++) {
      if (ans[i] >= th) {
          printf("%d %d\n", i, ans[i]);
          cnt++;
      }
  }
  printf("%d\n", cnt);

  return 0;
}
