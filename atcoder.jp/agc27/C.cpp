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

char s[210000];

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    scanf("%s", s);

    vector<int> cnt[2];
    cnt[0] = cnt[1] = vector<int>(n);
    vector<vector<int>> g(n);

    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
      cnt[s[a] - 'A'][b]++;
      cnt[s[b] - 'A'][a]++;
    }

    vector<int> bad;
    vector<bool> is_bad(n);
    for (int i = 0; i < n; i++) {
      if (!cnt[0][i] || !cnt[1][i]) {
        bad.push_back(i);
        is_bad[i] = true;
      }
    }

    for (int i = 0; i < (int)bad.size(); i++) {
      int v = bad[i];
      assert(is_bad[v]);
      for (int u : g[v]) {
        cnt[s[v] - 'A'][u]--;
        if (cnt[s[v] - 'A'][u] == 0 && !is_bad[u]) {
          is_bad[u] = true;
          bad.push_back(u);
        }
      }
    }

    static const char* answers[2] = {"Yes", "No"};

    printf("%s\n", answers[(int)bad.size() == n]);
  }

  return 0;
}
