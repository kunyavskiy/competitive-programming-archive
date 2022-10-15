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
  if ((a += b) >= MOD)
    a -= MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}
const int MOD2 = MOD - 1;

int mul2(int a, int b) { return (int)((a * 1LL * b) % MOD2); }

int mpow2(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul2(res, a);
    a = mul2(a, a);
    b >>= 1;
  }
  return res;
}



class RecursiveTournament {

  vector<int> get_counts(vector<string> v) {
    int n = v.size();
    vector<int> cnts(1 << n);
    for (int i = 0; i < (int)cnts.size(); i++) {
      cnts[i] = __builtin_popcount(i);
    }
    vector<int> g(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (v[i][j] == 'Y') {
          g[i] |= (1 << j);
        }
      }
    }

    vector<int> ans(n + 1);

    int ds[n];
    for (int mask = 1; mask < (1 << n); mask++) {
      int dspt = 0;
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
          ds[dspt++] = cnts[g[i] & mask];
        }
      }
      sort(ds, ds + dspt);
      dspt--;
      ans[cnts[mask]]++;
      int bal = 0;
      for (int i = 0; i < dspt; i++) {
        bal += ds[i];
        bal -= i;
        if (bal <= 0) {
          ans[cnts[mask]]--;
          break;
        }
      }
    }
    return ans;
  }

public:
    int count(vector <string> v, int k) {
    vector<int> cnt = get_counts(v);

    int ans = mpow(v.size(), k);
    for (int i = 2; i < (int)cnt.size(); i++) {
      for (int j = 0; j < k; j++) {
        int cur = cnt[i];
        cur = mul(cur, mpow(v.size(), j));
        int left = k - j - 1;
        // cur = cur * mpow((2 ^ (v.size() ^ left) - 1) ^ i
        int left_cnt = mpow(2, mpow2(v.size(), left));
        add(left_cnt, MOD - 1);
        int total = mpow(left_cnt, i);
        cur = mul(cur, total);

        add(ans, cur);
      }
    }
    return ans;
  }
};










