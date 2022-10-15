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


class StringTransformation {
public:
  bool getResult2(string from_, string to_) {
    auto convert = [](string s) {
      vector<pair<char, int>> ans;
      s += '$';
      int cnt = 1;
      for (int i = 1; i < (int) s.size(); i++) {
        if (s[i] != s[i - 1]) {
          ans.emplace_back(s[i - 1], cnt);
          cnt = 1;
        } else {
          cnt++;
        }
      }
      return ans;
    };

    auto from = convert(from_);
    auto to = convert(to_);
    if (from[0].first == to[0].first) {
      from[0].second--;
      to[0].second--;
    } else {
      return false;
    }
    if (from.back().first == to.back().first) {
      from.back().second--;
      to.back().second--;
    } else {
      return false;
    }

    vector<vector<bool>> dp(from.size() + 1, vector<bool>(to.size() + 1));
    dp[0][0] = true;
    for (size_t i = 0; i <= from.size(); i++) {
      for (size_t j = 0; j <= to.size(); j++) {
        if (!dp[i][j]) continue;
        if (i != from.size() && from[i].second % 2 == 0) {
          dp[i + 1][j] = true;
        }
        if (i != from.size() && j != to.size() && from[i].second >= to[j].second &&
            from[i].second % 2 == to[j].second % 2) {
          dp[i + 1][j + 1] = true;
        }
      }
    }
    return dp.back().back();
  }

  string getResult(string from_, string to_) {
    return getResult2(from_, to_) ? "YES" : "NO";
  }

};










