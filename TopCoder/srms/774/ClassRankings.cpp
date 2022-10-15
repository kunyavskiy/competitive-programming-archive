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

class ClassRankings {
  using dparr = vector<vector<vector<int>>>;
public:
    int countWays(vector <int> amt, vector <int> lo, vector <int> hi) {
      auto get_dp_arr = [&]() {
        return dparr(amt[0] + 1, vector<vector<int>>(amt[1] + 1, vector<int>(amt[2] + 1)));
      };

      vector<dparr> dd(3, get_dp_arr());
      dparr dp = get_dp_arr();
      dp[0][0][0] = 1;
      int from = *min_element(lo.begin(), lo.end());
      int to = *max_element(hi.begin(), hi.end());
      int ans = 0;
      for (int score = from; score <= to; score++) {
        dparr ndp = get_dp_arr();
        for (int a = 0; a <= amt[0]; a++) {
          for (int b = 0; b <= amt[1]; b++) {
            for (int c = 0; c <= amt[2]; c++) {
              if (!dp[a][b][c]) continue;
              for (int go = 0; go < 3; go++) {
                if ((go == 0 ? a : (go == 1 ? b : c)) < amt[go]) {
                  if (score < lo[go]) {
                    add(dd[go][a + (go == 0)][b + (go == 1)][c + (go == 2)], dp[a][b][c]);
                  } else if (score <= hi[go]) {
                    add(ndp[a + (go == 0)][b + (go == 1)][c + (go == 2)], dp[a][b][c]);
                  }
                }
              }
            }
          }
        }
        dp = ndp;
        for (int go = 0; go < 3; go++) {
          if (score == lo[go]) {
            for (int a = 0; a <= amt[0]; a++) {
              for (int b = 0; b <= amt[1]; b++) {
                for (int c = 0; c <= amt[2]; c++) {
                  add(dp[a][b][c], dd[go][a][b][c]);
                }
              }
            }
          }
        }
        add(ans, dp[amt[0]][amt[1]][amt[2]]);
      }
      return ans;
    }
};










