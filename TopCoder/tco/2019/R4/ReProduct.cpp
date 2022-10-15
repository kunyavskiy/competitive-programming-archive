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

const ll LIM = 1e18;

class ReProduct {
public:
  ll minimize(vector<int> base, int goal) {
    set<ll> vals;
    for (int i = 0; i < 10; i++) {
      vals.insert(i);
    }
    while (true) {
      set<ll> nvals;
      nvals.insert(0);
      for (ll x : vals) {
        for (int i = 1; i < 10;i++) {
          if (x <= LIM / i) {
            nvals.insert(x * i);
          }
        }
      }
      if (nvals.size() == vals.size()) {
        break;
      }
      vals = nvals;
//      eprintf("%d\n", (int)vals.size());
    }
    map<ll, int> dep;
    for (ll x : vals) {
      if (x < 10){
        dep[x] = base[x];
      } else {
        ll prod = 1;
        ll y = x;
        while (y) {
          prod *= y % 10;
          y /= 10;
        }
        assert(prod < x);
        assert(dep.count(prod));
        dep[x] = dep[prod] + 1;
      }
    }

    ll ans = LIM + 1;
    for (ll x : vals) {
      if (dep[x] == goal) {
        ans = min(ans, x);
      }
      if (dep[x] == goal - 1) {
        ll next = 0;
        if (x < 10) {
          next = 10 + x;
        } else {
          string s;
          ll y = x;
          for (int a = 9; a > 1; a--) {
            while (y % a == 0) {
              s += char('0' + a);
              y /= a;
            }
          }
          if (y != 1 || s.size() >= 18) {
            next = -1;
          } else {
            sort(s.begin(), s.end());
            next = 0;
            for (char c : s) {
              next = next * 10 + c - '0';
            }
            assert(next > x);
          }
        }
        if (next != -1) {
          ans = min(ans, next);
        }
      }
    }
    return ans;
  }
};










