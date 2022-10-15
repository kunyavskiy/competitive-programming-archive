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


class LeftToRightGame {
  vector<vector<int>> res;
  int mod;
  int len;

  int solve(int l, int r) {
    if (res[l][r] != -1) return res[l][r];
    int& ans = res[l][r];
    if (l == len) {
      if (l % 2 == 0) {
        return r != 0;
      }
      return r == 0;
    }
    for (int i = !l; i < 10; i++) {
      if (!solve(l + 1, (r * 10 + i) % mod)) {
        return ans = 1;
      }
    }
    return ans = 0;
  }

public:
  string whoWins(int len, int mod) {
    this->mod = mod;
    this->len = len;
    res = vector<vector<int>>(len + 1, vector<int>(mod, -1));
    return solve(0, 0) ? "Alice" : "Bob";
  }
};









class LeftToRightGame2 {
public:
  string whoWins(int len, int mod) {
    if (mod == 1) return "Bob";
    if (len & 1) return "Alice";
    if (mod <= 11) return "Bob";
    return "Alice";
  }
};











