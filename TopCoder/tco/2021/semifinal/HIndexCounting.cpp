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

class HIndexCounting {

  vector<vector<int>> splits;
  vector<vector<vector<int>>> splits_lim;

  int solve(int P, int C, int H) {
    if (H > P) return 0;
    int ans = 0;
    for (int i = H * H; i <= C; i++) {
      int lf = splits[H][i - H * H];
      int rg = splits_lim[H][P - H][C - i];
      add(ans, mul(lf, rg));
    }
    return ans;
  }

public:
    int count(int P, int C, int H) {
      splits = vector<vector<int>>(P + 1, vector<int>(C + 1));
      splits[0][0] = 1;
      for (int i = 1; i <= P; i++) {
        for (int j = 0; j <= C; j++) {
          add(splits[i][j], splits[i - 1][j]);
          if (j >= i) {
            add(splits[i][j], splits[i][j - i]);
          }
        }
      }
      splits_lim = vector<vector<vector<int>>>(P + 1, vector<vector<int>>(P+1, vector<int>(C+1)));
      splits_lim[0][0][0] = 1;
      for (int i = 0; i <= P; i++) {
        for (int j = 0; j <= P; j++) {
          for (int k = 0; k <= C; k++) {
            if (j > 0) {
              add(splits_lim[i][j][k], splits_lim[i][j - 1][k]);
            }
            if (k >= j && i > 0) {
              add(splits_lim[i][j][k], splits_lim[i - 1][j][k - j]);
            }
          }
        }
      }
      int ans1 = solve(P, C, H);
      //int ans2 = solve(P, C, H + 1);
      //sub(ans1, ans2);
      return ans1;
    }
};










