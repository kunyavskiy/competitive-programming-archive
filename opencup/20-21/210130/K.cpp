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

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  constexpr int INF = 1e9;
  vector<vector<int>> d(n, vector<int>(n, INF));
  for (int i = 0; i < n; i++) {
    d[i][i] = 0;
  }

  vector<vector<int>> ls(k);

  for (int w = 0; w < k; w++) {
    int s;
    scanf("%d", &s);
    ls[w].resize(s);
    for (int& v : ls[w]) {
      scanf("%d", &v); --v;
    }
  }
  int s;
  scanf("%d", &s);
  vector<int> o(s);
  for (int i = 0; i < s; i++) {
    scanf("%d", &o[i]); --o[i];
  }
  for (int i = 0; i < k; i++) {
    if (find(o.begin(), o.end(), i) == o.end()) {
      o.push_back(i);
    }
  }
  reverse(o.begin(), o.end());

  vector<int> anss;

  auto get_ans = [&] {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (d[i][j] < INF) {
          ans = max(ans, d[i][j]);
        }
      }
    }
    return ans;
  };

  anss.push_back(get_ans());

  for (int l : o) {
    vector<int> ds(n, INF);
    for (int i = 0; i < n; i++) {
      for (int v : ls[l]) {
        ds[i] = min(ds[i], d[i][v]);
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][j], ds[i] + ds[j] + 1);
      }
    }
    anss.push_back(get_ans());
  }

  reverse(anss.begin(), anss.end());
  for (int i = 0; i <= s; i++) {
    printf("%d\n", max(0, anss[i] - 1));
  }



}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int z;
  scanf("%d", &z);
  while (z-->0) {
    solve();
  }

  return 0;
}
