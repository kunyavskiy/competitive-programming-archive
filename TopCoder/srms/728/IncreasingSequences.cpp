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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

const int MAXN = 610;

class IncreasingSequences {

  int inv[MAXN];
  int dp[MAXN][MAXN];

public:
  int count(vector<int> L, vector<int> R) {
    for (int i = 1; i < MAXN; i++) {
      inv[i] = minv(i);
    }

    for (int i = 1; i < (int) L.size(); i++) {
      L[i] = max(L[i], L[i - 1] + 1);
    }
    for (int i = (int)R.size() - 2; i >= 0; i--) {
      R[i] = min(R[i], R[i + 1] - 1);
      if (L[i] > R[i]) return 0;
    }
    for (int& x : R) x++;

    vector<int> all;
    all.insert(all.begin(), L.begin(), L.end());
    all.insert(all.begin(), R.begin(), R.end());
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    for (int &x : L) {
      x = lower_bound(all.begin(), all.end(), x) - all.begin();
    }
    for (int &x : R) {
      x = lower_bound(all.begin(), all.end(), x) - all.begin();
    }

    return solve(all, L, R);
  }

  int solve(vector<int> all, vector<int> L, vector<int> R) {
    dp[0][0] = 1;
    for (int i = 0; i < (int) L.size(); i++) {
      for (int j = 0; j < R[i]; j++) {
        add(dp[i][j + 1], dp[i][j]);
        int len = all[j + 1] - all[j];
        int coef = 1;
        for (int k = i; k < (int) L.size() && L[k] <= j; k++) {
          coef = mul(coef, len - (k - i));
          coef = mul(coef, inv[k - i + 1]);
          add(dp[k + 1][j + 1], mul(dp[i][j], coef));
        }
      }
    }

    int ans = 0;
    for (int i = 0; i <= R.back(); i++) {
      add(ans, dp[L.size()][i]);
    }

    return ans;
  }
};










