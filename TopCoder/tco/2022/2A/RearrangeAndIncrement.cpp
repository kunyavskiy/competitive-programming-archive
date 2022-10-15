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


class RearrangeAndIncrement {
  void xtoone(int x, vector<int>& ans) {
    while (x != 1) {
      ans.push_back(x);
      if (x % 10 == 0) {
        x = x / 10;
      } else {
        x = x + (10 - x % 10);
      }
    }
  }

  void onetoy(int y, vector<int>& ans) {
    int init_size = ans.size();
    while (y != 1) {
      ans.push_back(y);
      if (y < 100) {
        y -= min(13, y - 1);
        continue;
      }
      auto s = to_string(y);
      int nz = count_if(s.begin(), s.end(), [](char c) { return c != '0';});
      if (y % 10 == 0) {
        if (nz == 1) {
          y -= 1;
          continue;
        }
        sort(s.begin() + 1, s.end());
        y = atoi(s.c_str());
        continue;
      } else {
        if (s[0] != '1') {
          if (s.back() == '1') {
            swap(s[0], s.back());
            sort(s.begin() + 1, s.end());
            y = atoi(s.c_str());
            continue;
          } else {
            y -= (y % 10 - 1);
            continue;
          }
        }
        y -= y % 10;
      }
    }
    reverse(ans.begin() + init_size, ans.end());
  }

public:
    vector <int> change(int x, int y) {
        vector<int> ans;
        xtoone(x, ans);
        ans.push_back(1);
        onetoy(y, ans);
        return ans;
    }
};










