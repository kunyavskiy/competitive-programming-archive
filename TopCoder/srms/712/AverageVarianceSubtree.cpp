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

const int MAXN = 50;

class AverageVarianceSubtree {
  vector<int> g[MAXN];
  vector<int> w;
  int n;

  ll tree_cnt[MAXN][MAXN];
  double avg[MAXN][MAXN];
  double avgsq[MAXN][MAXN];
  double avg2[MAXN][MAXN];
  int sz[MAXN];

  double ans = 0;
  double ans_cnt = 0;

  void add_ans(double d, double cnt) {
    double old_prob = ans_cnt;
    ans_cnt += cnt;
    old_prob /= ans_cnt;
    ans = ans * old_prob + d * (1.0 - old_prob);
    eprintf("d = %f, cnt = %f\n", d, cnt);
  }

  double merge(double a, double a2, int a_cnt, double b, double b2, int b_cnt) {
    double ret = a2 + b2 + 2 * a * b ;
    ret /= (a_cnt + b_cnt);
    ret /= (a_cnt + b_cnt);
    return ret;
  }

  void dfs(int v) {
    for (int u: g[v]) {
      dfs(u);
    }
    sz[v] = 1;
    tree_cnt[v][1] = 1;
    avg[v][1] = w[v];
    avgsq[v][1] = w[v] * 1.0 * w[v];
    avg2[v][1] = w[v] * 1.0 * w[v];
    for (int u: g[v]) {
      sz[v] += sz[u];
      for (int tot = sz[v]; tot > 0; tot--) {
        for (int i = 1; i <= sz[u] && i < tot; i++) {
          double old_prob = tree_cnt[v][tot];
          tree_cnt[v][tot] += tree_cnt[v][tot - i] * tree_cnt[u][i];
          if (tree_cnt[v][tot] == 0) continue;
          old_prob /= tree_cnt[v][tot];

          avg[v][tot] = (avg[v][tot] * old_prob) + (avg[v][tot - i] + avg[u][i]) * (1.0 - old_prob);
          avgsq[v][tot] = (avgsq[v][tot] * old_prob) + merge(avg[v][tot - i], avgsq[v][tot - i], tot - i, avg[u][i], avgsq[u][i], i) * (1.0 - old_prob);
          avg2[v][tot] = (avg2[v][tot] * old_prob) + (avg2[v][tot - i] + avg2[u][i]) * (1.0 - old_prob);
        }
      }
    }

    for (int i = 1; i <= sz[v]; i++) {
      if (tree_cnt[v][i] > 0) {
        add_ans(avg2[v][i] / i - avgsq[v][i], tree_cnt[v][i]);
      }
    }
  }

public:
  double average(vector<int> p, vector<int> w) {
    n = (int) w.size();
    this->w = w;
    for (int i = 1; i < n; i++) {
      g[p[i-1]].push_back(i);
    }

    dfs(0);

    return ans;
  }
};










