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


class ChromosomalCrossover {
public:
  int maximalLength(string _a, string _b) {
    int n = _a.size();
    vector<string> s;
    s.push_back(_a);
    s.push_back(_b);
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int l = 0; i + l <= n; l++) {
        ans = max(ans, l);
        if (s[0][i + l] != s[1][i + l]) break;
      }
      for (int j = i + 1; j < n; j++) {
        vector<bool> used[2];
        used[0] = used[1] = vector<bool>(n);
        for (int l = 0; j + l <= n; l++) {
          ans = max(ans, l);
          if (j + l == n) break;
          bool have[2] = {0, 0};
          for (int it = 0; it < 2; it++) {
            for (int jt = 0; jt < 2; jt++) {
              if (used[it][i + l]) continue;
              if (s[it][i + l] != s[jt][j + l]) continue;
              have[jt] = true;
            }
          }
          if (!have[0] && !have[1]) {
            break;
          } else if (have[0] && !have[1]) {
            used[0][j + l] = true;
          } else if (have[1] && !have[0]) {
            used[1][j + l] = true;
          }
        }
      }
    }
    return ans;
  }
};










