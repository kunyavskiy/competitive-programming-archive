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


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m, c;
  scanf("%d%d%d", &n, &m, &c);

  vector<vector<int>> all;
  map<vector<int>, int> id;
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
  for (int i = 0; i < (int) all.size(); i++) {
    id[all[i]] = i;
  }

  eprintf("all.size() = %d\n", (int)all.size());

  vector<vector<vector<int>>> next;
  next.resize(all.size(), vector<vector<int>>(m, vector<int>(c + 1, -1)));
  for (int i = 0; i < (int) all.size(); i++) {
    for (int j = 0; j < m; j++) {
      int upper = c;
      upper = min(upper, all[i][j]);
      if (j) upper = min(upper, all[i][j - 1]);
      for (int v = 0; v <= upper; v++) {
        vector<int> nv = all[i];
        for (int k = j; k < m && nv[k] > v; k++) nv[k] = v;
        assert(id.count(nv));
        next[i][j][v] = id[nv];
      }
    }
  }

  vector<int> dp(all.size());
  dp[id[vector<int>(m, c)]] = 1;


  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      TIMESTAMPf("%d %d", i, j);
      vector<int> ndp(all.size());
      int lower;
      scanf("%d", &lower);
      for (int k = 0; k < (int)all.size(); k++) {
        for (int v = lower; v <= c; v++) {
          if (next[k][j][v] != -1) {
            add(ndp[next[k][j][v]], dp[k]);
          }
        }
      }
      dp = ndp;
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
