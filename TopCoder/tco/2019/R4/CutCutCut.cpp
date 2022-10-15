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

const int C = 10000;

class CutCutCut {
public:
  vector<int> findPieces(vector<int> x1, vector<int> y1, vector<int> x2, vector<int> y2, int n) {
    auto conv = [](int x, int y) {
      if (y == 0) return x;
      if (x == C) return C + y;
      if (y == C) return 3 * C  - x;
      return 4 * C - y;
    };
    vector<pair<int, int>> v;
    int res = 1;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
      int a = conv(x1[i], y1[i]);
      int b = conv(x2[i], y2[i]);
      if (a > b) swap(a, b);
      res++;
      for (auto x : v) {
        bool f = x.first <= a && a <= x.second;
        bool s = x.first <= b && b <= x.second;
        if (f ^ s) {
          res++;
        }
      }
      ans.push_back(res);
      v.emplace_back(a, b);
    }
    return ans;
  }
};










