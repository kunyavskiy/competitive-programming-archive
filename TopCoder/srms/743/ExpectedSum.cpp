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


class ExpectedSum {
  double dp[2501][2501];
  double ndp[2501][2501];

public:
  double solve(vector<int> a, vector<int> p) {
    dp[0][0] = 1.0;

    int s = 0;

    for (int pos = 0; pos < (int) a.size(); pos++) {
      int olds = s;
      s += a[pos];
      for (int i = 0; i <= olds; i++) {
        for (int j = 0; j <= olds; j++) {
          {
            int ni = i + a[pos];
            int nj = max(j, ni);
            double nprob = dp[i][j] * (1.0 - p[pos] / 100.0);
            ndp[ni][nj] += nprob;
          }
          {
            int ni = max(0, i - a[pos]);
            int nj = j;
            double nprob = dp[i][j] * p[pos] / 100.0;
            ndp[ni][nj] += nprob;
          }
        }
      }
      for (int i = 0; i <= s; i++) {
        for (int j = 0; j <= s; j++) {
          dp[i][j] = ndp[i][j];
          ndp[i][j] = 0;
        }
      }
    }
    double ans = 0;
    for (int i = 0; i <= s; i++) {
      for (int j = 0; j <= s; j++) {
        ans += j * dp[i][j];
      }
    }
    return ans;
  }
};










