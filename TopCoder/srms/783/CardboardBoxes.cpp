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


class CardboardBoxes {
public:
    ll count(ll x) {
      if (x % 2) return 0;
      x /= 2;
      ll ans = 0;

      auto check = [&](ll apb, ll cpm) {
        ans += min(apb / 2, cpm - 1);
      };

      for (ll a = 1; a * a <= x; a++) {
        if (x % a == 0) {
          check(a, x / a);
          if (x / a != a) {
            check(x / a, a);
          }
        }
      }

      return ans;
    }
};










