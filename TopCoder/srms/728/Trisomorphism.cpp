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

const int MAXN = 100;

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


class Trisomorphism {
  int ans;
  int f[MAXN];
  int inv[MAXN];
  int invf[MAXN];

  int solve_inner(const vector<int> &cur) {
    int ans = 1;
    int n = 0;
    int count = 1;
    for (int a : cur) {
      n += a;
      count = mul(count, inv[a]);
      int tot = 0;
      for (int b : cur) {
        if (a % b == 0) {
          tot += b;
        }
      }
      ans = mul(ans, tot);
    }
    count = mul(count, f[n]);

    for (int i = 0; i < (int)cur.size();) {
      int j = i;
      while (j < (int)cur.size() && cur[i] == cur[j]) j++;
      count = mul(count, invf[j - i]);
      i = j;
    }
//    for (int x : cur) {
//      eprintf("%d ", x);
//    }
//    eprintf("ans = %d, count = %d\n", ans, count);
    return mul(ans, count);
  }

  void solve(vector<int> &cur, int minv, int sum, int sign) {
    if (sum == 0) {
      if (sign == 1) {
        add(ans, solve_inner(cur));
      }
      return;
    }
    if (minv > sum) {
      return;
    }
    solve(cur, minv + 1, sum, sign);
    cur.push_back(minv);
    solve(cur, minv, sum - minv, (minv % 2) ? sign : -sign);
    cur.pop_back();
  }

public:
  int maxSubset(int n) {

    f[0] = invf[0] = 1;
    for (int i = 1; i < MAXN; i++) {
      f[i] = mul(f[i - 1], i);
      inv[i] = minv(i);
      invf[i] = mul(invf[i - 1], inv[i]);
    }

    ans = 0;
    vector<int> tmp;
    solve(tmp, 1, n, 1);

    ans = mul(ans, 2);
    ans = mul(ans, invf[n]);
    return ans;
  }
};










