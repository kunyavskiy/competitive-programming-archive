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


class RandomConcat {
  int next(const vector<int>& p, int pos, const string& s, char c) {
      while (pos && s[pos] != c) pos = p[pos - 1];
      if (s[pos] == c) pos++;
      return pos;
  }

  vector<int> prefix(const string& s) {
      vector<int> p(s.size());
      for (int i = 1; i < (int) s.size(); i++) {
          p[i] = next(p, p[i - 1], s, s[i]);
      }
      return p;
  }

public:
    double expectation(vector<string> v, string s) {
        int n = v.size();
        vector<int> p = prefix(s);

        vector<vector<pair<int, int>>> go(v.size(), vector<pair<int, int>>(s.size()));

        for (int i = 0; i < (int) v.size(); i++) {
            for (int j = 0; j < (int) s.size(); j++) {
                int cur = j;
                int cnt = 0;
                for (char c : v[i]) {
                    cur = next(p, cur, s, c);
                    if (cur == (int) s.size()) {
                        cur = p[cur - 1];
                        cnt++;
                    }
                }
                go[i][j] = {cur, cnt};
            }
        }

        vector<vector<double>> dp(1 << n, vector<double>(s.size()));

        for (int i = (1 << n) - 2; i >= 0; i--) {
            for (int pos = 0; pos < (int)s.size(); pos++) {
                double tot = 0.0;
                int cnt = 0;
                for (int j = 0; j < n; j++) {
                    if (!(i & (1 << j))) {
                        cnt++;
                        tot += dp[i | (1 << j)][go[j][pos].first] + go[j][pos].second;
                    }
                }
                dp[i][pos] = tot / cnt;
            }
        }
        return dp[0][0];
    }
};










