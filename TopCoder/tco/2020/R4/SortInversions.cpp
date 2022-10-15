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


class SortInversions {
public:
  ll count(int n_) {
    ll n = n_;
    vector<ll> pw10 = {1};
    for (int i = 0; i < 18; i++) {
      pw10.push_back(pw10.back() * 10);
    }

    ll ans = 0;

    for (int l_large = 0; pw10[l_large] <= 10 * n; l_large++) {
      for (int l_small = 0; l_small < l_large; l_small++) {
        for (int pos_diff = 0; pos_diff < l_small; pos_diff++) {
          ll upper_bound = pw10[l_large] > n ? n : (pw10[l_large] - 1);
          ll lower_bound = pw10[l_large - 1];

          ll any_later_lower = (lower_bound / pw10[l_large - pos_diff]);
          ll any_later_upper = (upper_bound / pw10[l_large - pos_diff]);

          // n: >abcd99999
          // a:  abcdx...
          // b:  abcdy...
          ans += (any_later_upper - any_later_lower) * (45 - 9 * !pos_diff) * pw10[l_large - pos_diff - 1] * pw10[l_small - pos_diff - 1];

          // n:  abcde9999
          // a:  abcdx...
          // b:  abcdy...

          int e = (upper_bound / pw10[l_large - pos_diff - 1]) % 10;
          for (int d = !pos_diff; d < e; d++) {
            ans += (9 - d) * pw10[l_large - pos_diff - 1] * pw10[l_small - pos_diff - 1];
          }

          // n:  abcde...
          // a:  abcde...
          // b:  abcdx...

          ans += (9 - e) * (upper_bound % pw10[l_large - pos_diff - 1] + 1) * pw10[l_small - pos_diff - 1];
        }
      }
    }
/*
    vector<int> a;
    for (int i = 1; i <= n; i++) {
      a.push_back(i);
    }
    sort(a.begin(), a.end(), [](int a, int b) { return std::to_string(a) < std::to_string(b);});
    ll ans2 = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        if (a[j] > a[i]) {
          ans2++;
        }
      }
    }
    if (ans != ans2) {
      printf("%lld %lld %lld\n", n, ans, ans2);
      assert(false);
    }
*/
    ll ans2 = 0;
    for (int i = 1; i <= 9 && n >= pw10[i]; i++) {
      for (int j = 0; j <= 9; j++) {
        ll g = n / pw10[i+1];
        if (j < n /pw10[i] % 10) g++;
        if (!j) g--;
        g *= pw10[i];
        if (j == n / pw10[i] % 10) g += n % pw10[i] + 1;
        ans2 += (pw10[i] - 1) / 9 * (9 - j) * g;
      }
    }
    assert(ans == ans2);


    return ans;
  }
};










