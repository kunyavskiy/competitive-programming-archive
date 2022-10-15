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


class AqaAsadiTrains {
public:
  int getMax(vector<int> c, vector<int> a, vector<int> t_) {
    int k = c.size();
    int n = a.size();
    vector<vector<int>> t(k + 1, vector<int>(k + 1));
    for (int i = 0; i < k; i++) {
      t[k][i] = t[i][k] = i;
    }
    t[k][k] = k;
    for (int i = 0; i < k; i++) {
      for (int j = 0; j < k; j++) {
        t[i][j] = t_[i * k + j];
      }
    }

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(k + 1, -1e9)));

    for (int i = 0; i < n; i++) {
      dp[i][i+1][a[i]] = 0;
      dp[i][i+1][k] = c[a[i]];
    }
    for (int l = 2; l <= n; l++) {
      for (int i = 0; i + l <= n; i++) {
        int j = i + l;
        for (int s = i + 1; s < j; s++) {
          for (int x = 0; x <= k; x++) {
            for (int y = 0; y <= k; y++) {
              dp[i][j][t[x][y]] = max(dp[i][j][t[x][y]], dp[i][s][x] + dp[s][j][y]);
              dp[i][j][t[y][x]] = max(dp[i][j][t[y][x]], dp[i][s][x] + dp[s][j][y]);
            }
          }
        }
        for (int x = 0; x < k; x++) {
          dp[i][j][k] = max(dp[i][j][k], dp[i][j][x] + c[x]);
        }
      }
    }

    vector<int> dp2(n + 1, -1e9);
    dp2[0] = 0;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < i; j++) {
        for (int x = 0; x <= k; x++) {
          dp2[i] = max(dp2[i], dp2[j] + dp[j][i][x]);
        }
      }
    }
    return dp2.back();
  }
};










