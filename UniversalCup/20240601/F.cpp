#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  char s[3][11];
  scanf("%s", s[0]);
  scanf("%s", s[1]);
  scanf("%s", s[2]);
  vector<pair<char, int>> res;
  auto ans = [&](char c, int cycle) {
    if (res.empty() || res.back().first != c) {
      res.emplace_back(c, 1);
    } else {
      res.back().second++;
      if (res.back().second == cycle) res.pop_back();
    }
  };
  auto rot3 = [](char& a, char &b, char &c) {
    char tmp = a;
    a = b;
    b = c;
    c = tmp;
  };
  auto o = [&] { ans('o', 10);rotate(s[0], s[0] + 9, s[0] + 10); };
  auto g = [&] { ans('g', 10);rotate(s[1], s[1] + 9, s[1] + 10); };
  auto r = [&] { ans('r', 10);rotate(s[2], s[2] + 9, s[2] + 10); };
  auto c = [&] {
    ans('c', 3);
    rot3(s[0][0], s[1][0], s[2][0]);
    rot3(s[0][1], s[1][1], s[2][1]);
    rot3(s[0][2], s[1][2], s[2][2]);
  };

  while (count(s[0], s[0] + 10, 'o') != 10) {
    while (s[0][2] == 'o') o();
    if (count(s[2], s[2] + 10, 'o') != 0) {
      while (s[2][9] != 'o') r();
      c();
      r();
      c();
      c();
    } else {
      assert(count(s[1], s[1] + 10, 'o') != 0);
      while (s[1][9] != 'o') g();
      c();
      c();
      g();
      c();
    }
  }
  while (count(s[1], s[1] + 10, 'g') != 10) {
    assert(count(s[0], s[0] + 10, 'o') == 10);
    assert(count(s[2], s[2] + 10, 'g') != 0);
    while (s[1][2] == 'g') g();
    while (s[2][9] != 'g') r();
    c();
    c();
    r();
    c();
  }


  assert(string(s[0]) == string(10, 'o'));
  assert(string(s[1]) == string(10, 'g'));
  assert(string(s[2]) == string(10, 'r'));
  printf("%d\n", (int)res.size());
  for (auto [cc, cnt] : res) {
    printf("%c%d\n", cc, cnt);
  }
  return 0;
}
