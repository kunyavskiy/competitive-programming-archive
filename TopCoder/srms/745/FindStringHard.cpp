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


class FindStringHard {

  int anti(const string &s) {
    int cnt = 0;
    int n = (int) s.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i && i + j < n; j++) {
        if (s[i + j] != s[i - j - 1]) {
          cnt++;
        } else {
          break;
        }
      }
    }
    return cnt;
  }

public:
  string withAntipalindromicSubstrings(int n) {
    srand(1234);
    vector<bool> found(1001);
    vector<string> ans(1001);
    while (true) {
      int l = rand() % 100 + 1;
      string s = "a";
      while ((int)s.size() < l) {
        s += s.back() ^ ((rand() % 10 == 1) ? 0 : 3);
      }
      int x = anti(s);
      if (x < (int) found.size() && !found[x]) {
        found[x] = true;
        ans[x] = s;
        auto it = find(found.begin(), found.end(), false);
        if (it == found.end()) {
          break;
        }
//        eprintf("found %d(%s), %d not found yet\n", x, s.c_str(), (int) (it - found.begin()));
      }
    }
    return ans[n];
  }
};










