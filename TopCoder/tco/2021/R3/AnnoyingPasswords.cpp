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

class AnnoyingPasswords {
  int dp[30][30][30][4];

  int calc(int U, int L, int D, int prev) {
    if (U == 0 && L == 0 && D == 0) return 1;
    int &ans = dp[U][L][D][prev];
    if (ans != -1) return ans;
    ans = 0;
    if (U && prev != 0) add(ans, mul(26 - U + 1, calc(U - 1, L, D, 0)));
    if (L && prev != 1) add(ans, mul(26 - L + 1, calc(U, L - 1, D, 1)));
    if (D && prev != 2) add(ans, mul(10 - D + 1, calc(U, L, D - 1, 2)));
    return ans;
  }

public:
    int count(int U, int L, int D) {
        memset(dp, -1, sizeof(dp));
        return calc(U, L, D, 3);
    }
};










