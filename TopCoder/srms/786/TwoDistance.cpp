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


class TwoDistance {
public:
    ll findMinValue(int n, vector <int> p, vector <int> val_, int D, int seed) {
      vector<ll> val(n);
      {
        vector<unsigned> A(2 * n);
        A[0] = seed;
        for (int i = 1; i < 2* n; i++) {
          A[i] = (A[i - 1] * 1103515245LL + 12345LL) % 2147483648LL;
        }

        for (int i = 0; i < (int)val_.size(); i++) {
          val[i] = val_[i];
        }
        for (int i = val_.size(); i < n; i++) {
          val[i] = A[i];
        }

        p.reserve(n);
        for (int i = p.size(); i < n; i++) {
          p.push_back(A[n + i] % min(i, D));
        }
      }

      vector<vector<ll>> childs_val(n);
      vector<vector<ll>> grandchilds_val(n);
      for (int i = 1; i < n; i++) {
        childs_val[p[i]].push_back(val[i]);
        if (p[i] != 0) {
          grandchilds_val[p[p[i]]].push_back(val[i]);
        }
      }
      for (int i = 0; i < n; i++) {
        sort(childs_val[i].begin(), childs_val[i].end());
        sort(grandchilds_val[i].begin(), grandchilds_val[i].end());
      }
      auto find_closest_rng = [](vector<ll>::const_iterator b, vector<ll>::const_iterator e, ll val) {
        if (b == e) {
          return numeric_limits<ll>::max();
        }
        auto it = lower_bound(b, e, val);
        if (it == e) {
          return abs(val - *(e - 1));
        }
        ll ans = abs(val - *it);
        ++it;
        if (it != e) {
          ans = min(ans, abs(*it - val));
        }
        return ans;
      };

      auto find_closest = [&](const vector<ll>& vals, ll val) {
        return find_closest_rng(vals.begin(), vals.end(), val);
      };

      auto find_closest_except = [&](const vector<ll>& vals, ll val, ll except) {
        auto it = lower_bound(vals.begin(), vals.end(), except);
        assert(it != vals.end());
        return min(find_closest_rng(vals.begin(), it, val), find_closest_rng(it + 1, vals.end(), val));
      };


      ll ans = 0;

      for (int i = 0; i < n; i++) {
        ll cur = numeric_limits<ll>::max();
        for (ll x : grandchilds_val[i]) {
          cur = min(cur, find_closest_except(grandchilds_val[i], x, x));
        }
        if (i != 0) {
          for (ll x : grandchilds_val[i]) {
            cur = min(cur, find_closest_except(childs_val[p[i]], x, val[i]));
          }
          if (p[i] != 0) {
            cur = min(cur, find_closest_except(childs_val[p[i]], val[p[p[i]]], val[i]));
            cur = min(cur, find_closest(childs_val[i], val[p[p[i]]]));
          }
        }
        if (cur != numeric_limits<ll>::max()) {
          ans += cur;
        }
      }

      return ans;

    }
};










