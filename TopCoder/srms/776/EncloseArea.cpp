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


class EncloseArea {
public:
    vector <string> enclose(int n) {
        if (n % 2 == 1) return {};
        n /= 2;
        vector<string> ans(50, string(50, '.'));
        auto flip = [&](int x, int y, char c) {
          if (ans[x][y] == c) {
            ans[x][y] = '.';
          } else {
            assert(ans[x][y] == '.');
            ans[x][y] = c;
          }
        };

        int pos_x = 0;
        int pos_y = -1;

        for (int i = 0; i < n; i++) {
          ++pos_y;
          if (pos_y >= 60) {
            ++pos_x;
            pos_y = 0;
          }
          if (pos_x >= 30) {
            return {};
          }
          int shift_x = 2 * pos_x + (pos_y % 2);
          int shift_y = pos_y;
          if (shift_y + 1 >= 50 || shift_x + 1 >= 50) {
            i--;
            continue;
          }
          flip(shift_x, shift_y, '/');
          flip(shift_x, shift_y + 1, '\\');
          flip(shift_x + 1, shift_y, '\\');
          flip(shift_x + 1, shift_y + 1, '/');
        }
#ifdef LOCAL
        for (auto x : ans) {
          printf("%s\n", x.c_str());
        }
#endif
        return ans;
    }
};










