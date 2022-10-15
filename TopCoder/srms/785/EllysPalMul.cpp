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
#include <tuple>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;

class EllysPalMul {
public:
  int getMin(int n) {
    if (n % 10 == 0) return -1;
    vector<ll> d10;
    d10.push_back(1);
    while (d10.size() < 18) d10.push_back(10LL * d10.back());
    for (int length = 1; length <= 18; length++) {
      vector<vector<ll>> vals;
      for (int i = 0, j = length - 1; i <= j; i++, j--) {
        vals.emplace_back();
        ll val = (i == j ? d10[i] : (d10[i] + d10[j]));
        for (ll d = !i; d < 10; d++) {
          vals.back().emplace_back(d * val);
        }
      }
      int half = vals.size() / 2;
      auto mod_cmp = [&](ll a, ll b) {
        return std::make_tuple(a % n, a) < std::make_tuple(b % n, b);
      };
      auto get_all = [&](const vector<vector<ll>>&a) {
        vector<ll> res;
        res.emplace_back(0);
        for (const auto &x : a) {
          vector<ll> nres;
          nres.reserve(res.size() * x.size());
          for (ll y : x) {
            for (ll b : res) {
              nres.push_back(y + b);
            }
          }
          res = std::move(nres);
        }
        sort(res.begin(), res.end(), mod_cmp);
        return res;
      };
      vector<ll> a = get_all(vector<vector<ll>>(vals.begin(), vals.begin() + half));
      vector<ll> b = get_all(vector<vector<ll>>(vals.begin() + half, vals.end()));

      ll ans = numeric_limits<ll>::max();
      for (ll av : a) {
        auto it = lower_bound(b.begin(), b.end(), (n - av % n) % n, mod_cmp);
        if (it != b.end() && (av + *it) % n == 0) {
          ans = min(ans, av + *it);
        }
      }

      if (ans / n <= 1000000000) {
        return ans / n;
      }
    }

    return -1;
  }
};










