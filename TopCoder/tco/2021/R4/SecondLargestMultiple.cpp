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

struct SecondMax {
  ll a = -1, b = -1;
  void Update(ll x) {
    if (x > a) swap(a, x);
    if (x > b) swap(b, x);
  }
  void Update(const SecondMax &x) {
    Update(x.a);
    Update(x.b);
  }
};

SecondMax operator+(const SecondMax &a, const SecondMax &b) {
  SecondMax res;
  auto upd = [&](ll x, ll y) { if (x != -1 && y != -1) res.Update(x + y);};
  upd(a.a, b.a);
  upd(a.a, b.b);
  upd(a.b, b.a);
  upd(a.b, b.b);
  return res;
}


class SecondLargestMultiple {
public:
    ll find(ll N, int B) {
    vector<ll> ps(B + 1);
    ps[0] = 1;
    for (int i = 1; i <= B; i++) {
      ps[i] = ps[i - 1] * B;
    }
    vector<int> small;
    vector<int> large;
    for (int i = 0; i < B/2; i++) small.push_back(i);
    for (int i = B/2; i < B; i++) large.push_back(i);
    auto gen_ps = [](vector<int> v) {
      vector<vector<vector<int>>> ans;
      for (int l = 0; l <= (int)v.size(); l++) {
        ans.emplace_back();
        vector<int> perm = v;
        do {
          vector<int> t(perm.begin(), perm.begin() + l);
          if (ans.back().empty() || ans.back().back() != t)
            ans.back().push_back(t);
        } while (next_permutation(perm.begin(), perm.end()));
      }
      return ans;
    };
    vector<vector<vector<int>>> small_ps = gen_ps(small);
    vector<vector<vector<int>>> large_ps = gen_ps(large);
    SecondMax ans;
    ans.Update(0);
    for (int l = 1; l <= B; l++) {
      for (int smalls = 0; smalls < (1 << l); smalls++) {
        vector<int> pos_small, pos_large;
        for (int j = 0; j < l; j++) {
          if (smalls & (1 << j)) {
            pos_small.push_back(j);
          } else {
            pos_large.push_back(j);
          }
        }
        if (pos_small.size() > small.size() || pos_large.size() > large.size()) continue;
        auto gen_vals = [&](const vector<int>& pos, const vector<vector<vector<int>>> &perms) {
          map<ll, SecondMax> res;
          for (auto &perm: perms[pos.size()]) {
            if (pos.size() && perm[0] == 0 && pos[0] == l - 1) continue;
            ll score = 0;
            for (int i = 0; i < (int)pos.size(); i++) {
              score += perm[i] * ps[pos[i]];
            }
            res[score % N].Update(score);
          }
          return res;
        };
        map<ll, SecondMax> small_vals = gen_vals(pos_small, small_ps);
        map<ll, SecondMax> large_vals = gen_vals(pos_large, large_ps);
        for (auto x : large_vals) {
          auto it = small_vals.find((N - x.first) % N);
          if (it != small_vals.end()) {
            ans.Update(x.second + it->second);
          }
        }
      }
    }
    return ans.b;
  }
};










