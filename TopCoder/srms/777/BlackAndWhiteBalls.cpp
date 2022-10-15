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

class BlackAndWhiteBalls {
public:
    int getNumber(vector <int> v, int w, int b) {
        vector<int> dp1(v.size() + 1); // starts exactly at border
        vector<int> dp2(v.size() + 1); // starts somewhere inside

        dp2.back() = 1;

        for (int i = v.size() - 1; i >= 0; i--) {
          int cnt = (i % 2) ? b : w;

          {
            ll cur = 0;
            ll ans = 1;

            for (int j = i; j < (int) v.size(); j += 2) {
              if (j != i && cur % cnt == 0) {
                ans = mul(ans, v[j - 1] + 1);
              }
              cur += v[j];
              if (cur % cnt == 0) {
                add(dp1[i], mul(ans, dp2[j + 1]));
                add(dp1[i], mul(ans, mul((v[j] - 1) / cnt, dp1[j + 1])));
              } else {
                int here = v[j] - cur % cnt;
                add(dp1[i], mul(ans, mul((here - 1) / cnt + 1, dp1[j + 1])));
              }
            }
          }

          {
            ll from = 0;
            ll to = v[i];
            if (to >= w) {

            }
          }


        }

        return dp1[0];
    }
};










