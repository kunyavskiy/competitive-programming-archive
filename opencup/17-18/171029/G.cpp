#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

int my;

int bit(int r, int c) {
  return 1 << (3 * r + c);
}

map<pair<int, int>, pair<int, int>> cache;

bool all(int x, int y) {
  return (x & y) == y;
}

bool check_win(int x) {
  for (int i = 0; i < 3; i++) {
    if (all(x, 7 << (3 * i))) {
      return true;
    }
  }
  for (int i = 0; i < 3; i++) {
    if (all(x, ((1 << 0) | (1 << 3) | (1 << 6)) << i)) {
      return true;
    }
  }
  if (all(x, (1 << 0) | (1 << 4) | (1 << 8))) {
    return true;
  }
  return all(x, (1 << 2) | (1 << 4) | (1 << 6));
}

pair<int, int> go(int x, int y) {
  if (check_win(x) || check_win(y)) {
    return {-1, -1};
  }
  if ((x | y) == (1 << 9) - 1) {
    return {0, -1};
  }
  if (cache.find({x, y}) != cache.end()) {
    return cache[{x, y}];
  }
  auto &ans = cache[{x, y}];
  ans.first = ans.second = -1;

  int id = __builtin_popcount(x | y);
  for (int i = 0; i < 9; i++) {
    if ((x | y) & (1 << i)) continue;
    pair<int, int> r;
    if (id % 2 == 0) {
      r = go(x | (1 << i), y);
    } else {
      r = go(x, y | (1 << i));
    }
    r.first *= -1;
    r.second = i;
    ans = max(ans, r);
  }
  return ans;
}

int main() {
#ifdef LOCAL
//  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  char c;
  scanf("%c", &c);
  if (c == 'X') {
    my = 0;
  } else {
    my = 1;
  }

  int X[2];
  X[0] = X[1] = 0;
  for (int i = 0; i < 9; i++) {
    int x, y;
    if (i % 2 != my) {
      if (scanf("%d%d", &x, &y) != 2) {
        break;
      }
      --x, --y;
    } else {
      auto move = go(X[0], X[1]);
      int to = move.second;
      x = to / 3;
      y = to % 3;
      assert(bit(x, y) == (1 << to));
      printf("%d %d\n", x + 1, y + 1);
      fflush(stdout);
    }
    X[i % 2] |= bit(x, y);
    assert((X[0] & X[1]) == 0);

    /*for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        if (X[0] & (1 << (3 * j + k))) {
          printf("X");
        } else if (X[1] & (1 << (3 * j + k))) {
          printf("O");
        } else {
          printf(".");
        }
      }
      printf("\n");
    }*/
  }

  return 0;
}
