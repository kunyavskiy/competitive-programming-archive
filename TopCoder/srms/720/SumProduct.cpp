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


const int MAXN = 210;

class SumProduct {


  int cnk[MAXN][MAXN];
  int dp[MAXN];

  int solve(vector<int> cnt, int b) {
    if (*min_element(cnt.begin(), cnt.end()) < 0) return 0;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < 10; i++) {
      for (int j = b; j >= 0; j--) {
        for (int u = 1; u <= cnt[i] && u <= j; u++)
          add(dp[j], mul(dp[j - u], cnk[j][u]));
      }
    }
    return dp[b];
  }

public:
  int findSum(vector<int> cnt, int l1, int l2) {
    cnk[0][0] = 1;
    for (int i = 0; i < MAXN; i++) {
      for (int j = 0; j < MAXN; j++) {
        if (i) add(cnk[i][j], cnk[i - 1][j]);
        if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
      }
    }


    int coef = 0;
    int a = 1;
    for (int i = 0; i < l1; i++) {
      int b = 1;
      for (int j = 0; j < l2; j++) {
        add(coef, mul(a, b));
        b = mul(b, 10);
      }
      a = mul(a, 10);
    }

    int ans = 0;

    for (int t1 = 1; t1 <= 9; t1++) {
      cnt[t1]--;
      for (int t2 = 1; t2 <= 9; t2++) {
        cnt[t2]--;
        int x = solve(cnt, l1 + l2 - 2);
        x = mul(x, t1);
        x = mul(x, t2);
        add(ans, x);
        cnt[t2]++;
      }
      cnt[t1]++;
    }
    return mul(ans, coef);
  }
};










