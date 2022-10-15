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


class LandSplitter {
public:
    ll cheapest(int n, int a, int b) {
        if (a == b) {
          if (n % a != 0) {
            return -1;
          }
          ll cnt = n / a;
          return (ll(n) * n - ll(cnt) * a * a) / 2;
        }
        ll ans = -1;
        for (int k = 0; k <= n / b; k++) {
          int other = n - k * b;
          if (other < a) continue;
          int rem = other % a;
          if (a + rem > b) continue;

          ll large = (min(b, other) - rem - a) / a * a + rem + a;
          if (!(a <= large && large <= b)) continue;
          ll score = ll(k) * b * b;
          score += large * large;
          other -= large;
          assert(other % a == 0);
          score += ll(a) * other;
          ans = max(ans, score);
        }

        if (ans == -1)
          return ans;

        return (ll(n) * n - ans) / 2;
    }
};










