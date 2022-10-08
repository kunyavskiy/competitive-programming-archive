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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> used(1 << n);
  set<vector<int>> ids;
  for (int i = 0; i < (1 << n); i++) {
    if (used[i]) continue;
    auto norm = [&](int x) {
      vector<int> ids;
      for (int i = 0; i < n; i++) {
        if (x & (1 << i)) {
          int xx = i % 3;
          if (ids.size() >= 2 && ids[ids.size() - 1]  == (i + 2) % 3 && ids[ids.size() - 2] == (i + 1) % 3) {
            ids.pop_back();
            ids.pop_back();
          } else {
            ids.push_back(xx);
          }
        }
      }
      return ids;
    };
    assert(ids.insert(norm(i)).second);
    function<void(int)> dfs = [&](int x) {
      if (used[x]) return;
      assert(norm(x) == norm(i));
      used[x] = true;
      printf("%d ", x);
      for (int i = 0; i + 3 <= n; i++) {
        if ((((x >> i) & 7) == 0) || (((x >> i) & 7) == 7)) {
          dfs(x ^ (7 << i));
        }
      }
    };
    for (int x : norm(i)) {
      printf("%d ", x);
    }
    printf(":");
    dfs(i);
    printf("\n");
  }

  return 0;
}
