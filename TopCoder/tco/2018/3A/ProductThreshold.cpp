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


class ProductThreshold {

  ll solve(vector<int> a, int lim) {
    ll prod = 1;
    int l = 0;
    int cnt[2];
    cnt[0] = 0;
    cnt[1] = 0;
    int my_sign = 0, l_sign = 0;
    ll ans = 0;
    for (int i = 0; i < (int)a.size(); i++) {
      prod *= abs(a[i]);
      if (a[i] < 0) my_sign ^= 1;
      while (prod > lim) {
        cnt[l_sign]++;
        prod /= abs(a[l]);
        if (a[l] < 0) l_sign ^= 1;
        l++;
      }
      ans += cnt[my_sign];
    }
    return ans;
  }

public:
  ll subarrayCount(int N, int limit, vector<int> A, int s, int o) {
    ll seed = A.back();
    while ((int)A.size() < N) {
      seed = (seed * 1103515245 + 12345) & ((1LL << 31) - 1);
      A.push_back(seed % s + o);
    }
    int prev = 0;
    ll ans = N * (N + 1) / 2;
    for (int i = 0; i < N; i++) {
      if (A[i] == 0) {
        ans -= solve(vector<int>(A.begin() + prev, A.begin() + i), limit);
        prev = i + 1;
      }
    }
    ans -= solve(vector<int>(A.begin() + prev, A.end()), limit);
    return ans;
  }
};







class ProductThreshold2 {

  int mul(int a, int b, int lim) {
    ll res = a * 1LL * b;
    if (abs(res) > lim) {
      if (res > 0) res = lim + 1;
      else res = -(lim + 1);
    }
    return res;
  }

public:
  ll subarrayCount(int N, int limit, vector<int> A, int s, int o) {
    ll seed = A.back();
    while ((int)A.size() < N) {
      seed = (seed * 1103515245 + 12345) & ((1LL << 31) - 1);
      A.push_back(seed % s + o);
    }

    ll ans = 0;

    for (int i = 0; i < N; i++) {
      int res = 1;
      for (int j = i; j < N; j++) {
        res = mul(res, A[j], limit);
        if (res <= limit) {
          ans++;
        }
      }
    }
    return ans;
  }
};













