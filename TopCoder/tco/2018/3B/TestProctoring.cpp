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


class TestProctoring {
public:
  double expectedTime(vector<int> a, vector<int> b) {
    int n = a.size();
    vector<double> p(n), q(n);
    for (int i = 0; i < n; i++) {
      p[i] = a[i] * 1.0 / b[i];
      q[i] = 1.0 - p[i];
    }
    vector<vector<double>> dp(1 << n, vector<double>(n, 0));

    for (int i = 1; i < (1 << n); i++) {
      for (int j = 0; j < n; j++) {
        double &ans = dp[i][j];
        double prob = 1.0;
        int cur = j;
        for (int k = 0; k < n; k++) {
          if (i & (1 << cur)) {
            ans += prob * p[cur] * dp[i ^ (1 << cur)][cur];
            prob *= q[cur];
          }
          cur++;
          if (cur >= n) {ans += prob; cur -= n; }
        }
        ans /= 1.0 - prob;
      }
    }

    return dp[(1 << n) - 1][0] + 1;
  }
};










