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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

typedef pair<int, int> state;

ll eval(const vector<int>& v) {
  ll x = 0;
  for (int i : v) {
    x = 11 * x + i;
  }
  return x;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m, c;
  scanf("%d%d%d", &n, &m, &c);
//  n = m = c = 10;

  vector<vector<int>> all;
  map<ll, int> id;
  for (int i = 0; i <= c; i++) {
    all.push_back(vector<int>(1, i));
  }
  while ((int)all[0].size() < m) {
    vector<vector<int>> nall;
    for (auto x : all) {
      int lim = x.back();
      x.push_back(0);
      for (int j = 0; j <= lim; j++) {
        x.back() = j;
        nall.push_back(x);
      }
    }
    all = nall;
  }

  eprintf("all.size() = %d\n", (int)all.size());
  TIMESTAMP("all");

  for (int i = 0; i < (int) all.size(); i++) {
    id[eval(all[i])] = i;
  }

  TIMESTAMP("id");


  vector<vector<int>> next;
  next.resize(all.size(), vector<int>(m, -1));
  for (int i = 0; i < (int) all.size(); i++) {
    for (int j = 0; j < m; j++) {
      vector<int> nv = all[i];
      int v = all[i][j] - 1;
      if (v == -1) continue;
      for (int k = j; k < m && nv[k] > v; k++) nv[k] = v;
      next[i][j] = id[eval(nv)];
    }
  }
  TIMESTAMP("next");

  vector<int> dp(all.size());
  dp[id[eval(vector<int>(m, c))]] = 1;


  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int lower;
      scanf("%d", &lower);
//      lower = 0;
      for (int k = (int)all.size() - 1; k >= 0; k--) {
        if (all[k][j] > lower) {
          add(dp[next[k][j]], dp[k]);
        }
      }

      /*
      for (int k = 0; k < (int)all.size(); k++) {
        if (dp[k] > 0) {
          eprintf("%d * [", dp[k]);
          for (int x : all[k]) {
            eprintf("%d ", x);
          }
          eprintf("] + ");
        }
      }
      eprintf("\n");
       */

    }
  }

  int ans = 0;
  for (int x : dp) {
    add(ans, x);
  }

  printf("%d\n", ans);

  return 0;
}
