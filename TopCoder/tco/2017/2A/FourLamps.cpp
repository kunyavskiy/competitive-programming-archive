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


class FourLamps {

  ll dp[55][55];

public:
  ll count(string s, int k) {
    vector<int> ok;
    for (int i = 2; i + 2 <= (int) s.size(); i++) {
      int cnt = 0;
      for (int j = i - 2; j < i + 2; j++) {
        if (s[j] == '1')
          cnt++;
      }
      if (cnt % 2 == 1) {
        ok.push_back(1);
      } else {
        ok.push_back(0);
      }
    }
    dp[0][0] = 1;

    for (int i = 0; i < (int)ok.size(); i++) {
      for (int ops = 0; ops <= i; ops++) {
        if (dp[i][ops] == 0) continue;
        dp[i + 1][ops] += dp[i][ops];
        int cnt = 0;
        for (int j = 0; i + j < (int) ok.size(); j++) {
          cnt += ok[i + j];
          if (cnt % 2 == 1) {
            dp[i + j + 2][ops + j + 1] += dp[i][ops];
          }
        }
      }
    }

    ll ans = 0;
    for (int ops = 0; ops <= (int)ok.size() && ops <= k; ops++) {
      ans += dp[ok.size()][ops] + dp[ok.size() + 1][ops];
    }

    if (k == 1 || ans == 1) {
      return 2 * ans - 1;
    }
    return 2 * ans;
  }
};










