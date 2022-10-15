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


class PermuteTheArray {
  vector<vector<pair<int, int>>> g;
  vector<int> comp_id;
  vector<int> col;
  vector<int> comp_color;
  vector<int> comp_cnt[2];
  bool fail;

  void dfs(int v, int comp, int c) {
      if (comp_id[v] != -1) {
          if (col[v] != c) {
              fail = true;
          }
          return;
      }
      comp_id[v] = comp;
      col[v] = c;
      comp_cnt[c][comp]++;
      for (auto to : g[v]) {
          dfs(to.first, comp, c ^ to.second);
      }
  }

public:
  vector<int> getPermutation(vector<int> A, vector<int> x, vector<int> y, vector<int> d) {
      int n = (int)A.size();
      g.resize(n);
      for (int i = 0; i < (int) x.size(); i++) {
          g[x[i]].emplace_back(y[i], d[i]);
          g[y[i]].emplace_back(x[i], d[i]);
      }

      fail = false;
      comp_id = vector<int>(n, -1);
      col = vector<int>(n, -1);

      for (int i = 0; i < n; i++) {
          if (comp_id[i] == -1) {
              comp_cnt[0].push_back(0);
              comp_cnt[1].push_back(0);
              dfs(i, comp_color.size(), 0);
              comp_color.push_back(-1);
          }
      }
      if (fail) {
          return vector<int>();
      }

      vector<vector<vector<int>>> dp(comp_color.size() + 1, vector<vector<int>>(n + 1, vector<int>(n + 1)));
      dp.back()[0][0] = true;
      for (int i = (int)comp_color.size() - 1; i >= 0; i--) {
          for (int j = 0; j <= n; j++) {
              for (int k = 0; k <= n; k++) {
                  dp[i][j][k] = dp[i + 1][j][k];
                  if (j >= comp_cnt[0][i] && k >= comp_cnt[1][i]) {
                      dp[i][j][k] |= dp[i + 1][j - comp_cnt[0][i]][k - comp_cnt[1][i]];
                  }
                  if (k >= comp_cnt[0][i] && j >= comp_cnt[1][i]) {
                      dp[i][j][k] |= dp[i + 1][j - comp_cnt[1][i]][k - comp_cnt[0][i]];
                  }
              }
          }
      }

      int have[2];
      have[0] = have[1] = 0;
      for (int x : A) {
          have[x % 2]++;
      }

      if (!dp[0][have[0]][have[1]]) {
          return vector<int>();
      }

      sort(A.begin(), A.end());

      vector<int> ans;
      for (int i = 0; i < n; i++) {
          bool allow[2];
          int cid = comp_id[i];
          if (comp_color[cid] != -1) {
              allow[comp_color[cid] ^ col[i] ^ 0] = true;
              allow[comp_color[cid] ^ col[i] ^ 1] = false;
          } else {
              allow[0] = have[0] >= comp_cnt[0][cid] && have[1] >= comp_cnt[1][cid] && dp[cid + 1][have[0] - comp_cnt[0][cid]][have[1] - comp_cnt[1][cid]];
              allow[1] = have[0] >= comp_cnt[1][cid] && have[1] >= comp_cnt[0][cid] && dp[cid + 1][have[0] - comp_cnt[1][cid]][have[1] - comp_cnt[0][cid]];
          }
          for (int j = 0; j <= (int)A.size(); j++) {
              assert(j < (int)A.size());
              if (allow[A[j] % 2]) {
                  ans.push_back(A[j]);
                  if (comp_color[cid] == -1) {
                      comp_color[cid] = col[i] ^ (A[j] % 2);
                      have[comp_color[cid]] -= comp_cnt[0][cid];
                      have[!comp_color[cid]] -= comp_cnt[1][cid];
                  } else {
                      assert(comp_color[cid] == (col[i] ^ (A[j] % 2)));
                  }
                  A.erase(A.begin() + j);
                  break;
              }
          }
      }
      return ans;
  }
};
