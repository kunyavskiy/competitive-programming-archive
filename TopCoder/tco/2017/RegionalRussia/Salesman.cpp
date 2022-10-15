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


class Salesman {

  int solve(vector<int> p, vector<int> d) {
    int n = d.size();
    int last_neg = -1;
    int first_neg = -1;
    for (int i = n - 1; i >= 0; i--) {
      if (d[i] < 0) {
        if (last_neg == -1) {
          last_neg = i;
        }
        first_neg = i;
      }
    }
    if (last_neg == -1) return 0;
    int last = first_neg;
    int nlast = last_neg;
    ll need = 0;
    for (int i = 0; i < n; i++) {
      if (d[i] < 0) {
        need -= d[i];
      }
    }
    for (int i = first_neg; i <= last_neg; i++) {
      if (d[i] >= 0) {
        need -= d[i];
      }
    }
    ll bal = 0;

    for (int i = 0; i <= last_neg; i++) {
      if (p[i] >= 0 && d[i] >= 0) {
        bal += d[i];
      }
    }

    while (need > 0 && last > 0) {
      last--;
//      assert(d[last] >= 0);
      need -= d[last];
    }

    while (need > 0) {
      last_neg++;
//      assert(last_neg < n);
//      assert(d[last_neg] >= 0);
      need -= d[last_neg];
      bal += d[last_neg];
    }

    int ans = (int) 1e9;

    do {

      while (need + d[last] <= 0 && last < first_neg) {
        need += d[last];
        last++;
      }

      nlast = max(nlast, last);

      while (nlast > last) {
        if (d[nlast] >= 0) {
          if (p[nlast] < 0) {
            bal += d[nlast];
          }
          nlast--;
        } else {
          if (bal >= -d[nlast]) {
            bal += d[nlast];
            nlast--;
          } else {
            break;
          }
        }
      }

      ans = min(ans, abs(p[last_neg]) + p[last_neg] - 2 * p[last] + p[nlast]);

      last_neg++;
      if (last_neg < n) {
        bal += d[last_neg];
        need -= d[last_neg];
      }
    } while (last_neg < n);

    //assert(ans == solve_slow(p, d));
    return ans;
  }


  int solve_shift(vector<int> p, vector<int> d) {
    int ans = solve(p, d);
    for (int i = 0; i < (int)p.size(); i++) {
      vector<int> np = p;
      for (int j = 0; j < (int)p.size(); j++) {
        np[j] -= p[i];
      }
      ans = min(ans, solve(np, d) + abs(p[i]));
    }
    return ans;
  }

public:
  int minMoves(vector<int> p, vector<int> d) {
    int n = (int) p.size();
    int ans = solve_shift(p, d);
    for (int i = 0; i < n; i++) {
      p[i] *= -1;
    }
    reverse(p.begin(), p.end());
    reverse(d.begin(), d.end());
    int ans2 = solve_shift(p, d);

    return min(ans, ans2);
  }
};










