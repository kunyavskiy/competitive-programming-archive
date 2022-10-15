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


class ABBAReplace {
  int solve_stupid(string s) {
    int ans = 0;
    while (true) {
      bool any = false;
      for (int i = 0; i + 1 < (int)s.size(); i++) {
        if (s[i] == 'A' && s[i + 1] == 'B') {
          swap(s[i], s[i + 1]);
          i++;
          any = true;
        }
      }
      if (any) {
        ans++;
      } else {
        break;
      }
    }
    return ans;
  }
public:
    int countSteps(string s, int n, int seed, int t) {
      while ((int)s.size() < n) {
        seed = (seed * 1103515245LL + 12345) & 0x7fffffff;
        if (seed < t) {
          s += 'A';
        } else {
          s += 'B';
        }
      }

      int ans = 0;
      int cnta = 0;
      for (char c : s) {
        if (c == 'A') {
          cnta++;
        } else {
          if (cnta != 0) {
            ans = max(ans + 1, cnta);
          }
        }
      }
#ifdef LOCAL
      assert(ans == solve_stupid(s));
#endif
      return ans;
    }
};










