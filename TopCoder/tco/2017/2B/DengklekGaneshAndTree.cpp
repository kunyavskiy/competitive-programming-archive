#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

class DengklekGaneshAndTree {
  vector<vector<int>> g;
  vector<int> h;
  int n;

  int maxh;
  vector<bool> used;

  void dfsh(int v) {
    for (int u : g[v]) {
      h[u] = h[v] + 1;
      dfsh(u);
    }
  }

  void dfsl(int v, const string& l) {
    maxh = max(maxh, h[v]);
    used[v] = true;
    for (int u : g[v]) {
      if (l[u] == l[v]) {
        dfsl(u, l);
      }
    }
  }

public:
  int getCount(string l, vector<int> p) {
    n = (int) l.size();
    h = vector<int>(n);
    g = vector<vector<int>>(n);
    for (int i = 1; i < n; i++) {
      g[p[i-1]].push_back(i);
    }

    dfsh(0);
    used = vector<bool>(n);

    vector<pair<int, int>> segs;

    for (int i = 0; i < n; i++) {
      if (used[i]) continue;
      maxh = h[i];
      dfsl(i, l);
      segs.push_back({h[i], maxh + 1});
    }

    sort(segs.begin(), segs.end());

    int maxh = *max_element(h.begin(), h.end());

    vector<int> dp(maxh + 2);
    dp[0] = 1;

    for (auto x : segs) {
      int lf = x.first;
      int rg = x.second;
      vector<int> ndp(maxh + 2);

      for (int i = lf; i <= maxh + 1; i++) {
        add(ndp[i], dp[i]);
        add(ndp[max(i, rg)], dp[i]);
      }

      dp = ndp;
    }

    return dp[maxh + 1];
  }
};










