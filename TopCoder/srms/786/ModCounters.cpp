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

class ModCounters {
public:
    int findExpectedSum(vector <int> v, int A0, int X, int Y, int n, int k) {
      {
        vector<int> a;
        a.push_back(A0);
        while ((int) a.size() < n) {
          a.push_back((a.back() * 1LL * X + Y) % 1812447359);
        }
        while ((int) v.size() < n) {
          v.push_back(a[v.size()] % 512);
        }
      }

      vector<int> f(k + 1);
      vector<int> invf(k + 1);
      f[0] = invf[1] = 1;
      for (int i = 1)

    }
};










