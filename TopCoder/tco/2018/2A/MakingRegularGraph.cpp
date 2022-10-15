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


class MakingRegularGraph {
public:
  vector<int> addEdges(int n, vector<int> x, vector<int> y) {
    vector<int> deg(n);
    vector<vector<bool>> g(n, vector<bool>(n, false));
    for (int i = 0; i < (int)x.size(); i++) {
      g[x[i]][y[i]] = g[y[i]][x[i]] = true;
      deg[x[i]]++;
      deg[y[i]]++;
    }

    vector<int> cnt(3);
    for (int i = 0; i < n; i++) {
      cnt[deg[i]]++;
    }

    auto is_bad = [&n, &g, &deg](const vector<int>& x) {
      if (x[2] == n) return false;
      if (x[0] + x[1] >= 3) return false;
      if (x[0] > 0) return true;
      assert(x[1] == 2);
      int a, b;
      a = b = -1;
      for (int i = 0; i < n; i++) {
        if (deg[i] == 1) {
          if (a == -1) a = i;
          else b = i;
        }
      }
      return (bool)g[a][b];
    };

    if (is_bad(cnt)) return {-1};

    vector<int> ans;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (deg[i] == 2 || deg[j] == 2) continue;
        if (g[i][j]) {
          continue;
        }
        vector<int> ncnt = cnt;
        ncnt[deg[i]]--;
        ncnt[deg[j]]--;
        ncnt[deg[i] + 1]++;
        ncnt[deg[j] + 1]++;
        g[i][j] = g[j][i] = 1;
        deg[i]++;
        deg[j]++;
        if (is_bad(ncnt)) {
          g[i][j] = g[j][i] = 0;
          deg[i]--;
          deg[j]--;
          continue;
        }
        ans.push_back(i);
        ans.push_back(j);
        cnt = ncnt;
      }
    }
    return ans;
  }
};










