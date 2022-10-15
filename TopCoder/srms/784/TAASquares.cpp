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


class TAASquares {
public:
  vector<string> construct(int n) {
    vector<string> ans(n, string(n, '0'));
    vector<int> cnt(2 * n + 1);
    vector<int> sumr(n);
    vector<int> sumc(n);
    int distinct = 1;
    cnt[0] = 2 * n;
    auto rem_cnt = [&](int val) {
      cnt[val]--;
      if (cnt[val] == 0) distinct--;
    };
    auto add_cnt = [&](int val) {
      if (cnt[val] == 0) distinct++;
      cnt[val]++;
    };

    vector<string> best = ans;
    int best_val = distinct;

    auto set = [&](int x, int y, char c) {
      rem_cnt(sumr[x]);
      sumr[x] += c - ans[x][y];
      add_cnt(sumr[x]);

      rem_cnt(sumc[y]);
      sumc[y] += c - ans[x][y];
      add_cnt(sumc[y]);

      ans[x][y] = c;
      if (distinct > best_val) {
        best_val = distinct;
        best = ans;
      }
    };

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i > j) {
          set(i, j, '2');
        } else if (i == j && i >= (n + 1) / 2) {
          set(i, j, '1');
        }

      }
    }
    /*
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - 1; j++) {
        if (i <= j) {
          set(i, j, '2');
        } else {
          set(i, j, '0');
        }
      }
    }
    for (int i = 0; i < n - 1; i++) {
      set(n - 1, i, '0');
      set(i, n - 1, '1');
    }

    const int IT = 5e6;
    const double C = 1.0;

    for (int i = 0; i < IT; i++) {
      int x = rand() % n;
      int y = rand() % n;
      int old_distinct = distinct;
      char oldc = ans[x][y];
      set(x, y, rand() % 3 + '0');
      double prob = exp((distinct - old_distinct) * 1.0 / IT * (IT - i) * C);
//      if (i % 10000 == 0) {
//        eprintf("%d -> %d %lf\n", distinct, old_distinct, exp((distinct - old_distinct) * 1.0 / IT * (IT - i) * C));
//      }
      if (drand48() > prob) {
        set(x, y, oldc);
      }
    }
*/
    ans = best;
    vector<int> sums;
    for (int i = 0; i < n; i++) {
      int s = 0;
      for (int j = 0; j < n; j++) {
        s += ans[i][j] - '0';
      }
      sums.push_back(s);
    }
    for (int i = 0; i < n; i++) {
      int s = 0;
      for (int j = 0; j < n; j++) {
        s += ans[j][i] - '0';
      }
      sums.push_back(s);
    }
    sort(sums.begin(), sums.end());
    sums.erase(unique(sums.begin(), sums.end()), sums.end());
    eprintf("%d %d %d\n", n, (int) sums.size(), 2 * n - (int)sums.size());

    return ans;
  }
};










