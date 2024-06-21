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

struct Evaluator {
  explicit Evaluator(string s) : val(std::move(s)), pos(0) {}
  string val;
  int pos;
  bool feed(char c) {
    if (pos < (int)val.size() && val[pos] == c) {
      pos++;
      return true;
    }
    return false;
  }
  int eval() {
    pos = 0;
    int res = get_xor();
    assert(pos == (int)val.size());
    return res;
  }
private:
  int get_xor() {
    int r = get_or();
    while (feed('^')) {
      r = r ^ get_or();
    }
    return r;
  }
  int get_or() {
    int r = get_and();
    while (feed('|')) {
      r = r | get_and();
    }
    return r;
  }
  int get_and() {
    int r = get_eq();
    while (feed('&')) {
      r = r & get_eq();
    }
    return r;
  }

  int get_eq() {
    int r = get_term();
    while (feed('=')) {
      r = (r ^ get_term()) ^ 0b1111;
    }
    return r;
  }

  int get_term() {
    if (feed('(')) {
      int res = get_xor();
      bool x = feed(')');
      assert(x);
      return res;
    }
    if (feed('0')) return 0b0000;
    if (feed('1')) return 0b1111;
    if (feed('x')) return 0b1100;
    if (feed('y')) return 0b1010;
    if (feed('!')) return get_term() ^ 0b1111;
    assert(false);
  }
};


int read_mask() {
  static char s[1'100'100];
  scanf("%s", s);
  return Evaluator(s).eval();
}

struct cond {
  int id1, id2, mask, val;
};

vector<cond> conds;

template<typename T>
int solve(int pos, int s1, int s2, int e, vector<int> &vals, const T &next) {
  assert(pos < (int)conds.size());
  auto [id1, id2, mask, val] = conds[pos];
  id1 += s1;
  id2 += s2;

  auto options = [&](auto matched, auto unmatched) {

    for (int i = 0; i <= 1; i++) {
      if (vals[id1] == 1 - i) continue;
      for (int j = 0; j <= 1; j++) {
        if (vals[id2] == 1 - j) continue;
        if (id1 == id2 && (i != j)) continue;
        if (mask & (1 << (2 * i + j))) {
          matched(i, j);
        } else {
          unmatched(i, j);
        }
      }
    }
  };
  int cnt_matched = 0, cnt_unmatched = 0;
  options([&](int, int){ cnt_matched++; }, [&](int, int) { cnt_unmatched++; } );
  if (cnt_matched == 0) return solve(pos+1, s1, s2, e, vals, next);
  auto with = [&](int v1, int v2, auto todo) {
    int ov1 = vals[id1];
    int ov2 = vals[id2];
    vals[id1] = v1;
    vals[id2] = v2;
    todo();
    vals[id1] = ov1;
    vals[id2] = ov2;
  };
  int ans = 0;
  if (val == e) {
    if (cnt_unmatched == 0) return next(vals);
    options(
        [&](int a, int b) { with(a, b, [&] { ans += next(vals); }); },
        [&](int a, int b) { with(a, b, [&] { ans += solve(pos+1, s1, s2, e, vals, next); }); }
        );
  } else {
    if (cnt_unmatched == 0) return 0;
    options(
        [&](int, int) {},
        [&](int a, int b) { with(a, b, [&] { ans += solve(pos+1, s1, s2, e, vals, next); }); }
    );
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, k;
  scanf("%d%d", &n, &k);
  {
    vector<cond> all;
    for (int i = 0; i < n; i++) {
      int b1, b2;
      scanf("%d%d", &b1, &b2);
      int mask = read_mask();
      int val;
      scanf("%d", &val);
      all.push_back({b1 - 1, b2 - 1, mask, val});
    }
    int last;
    scanf("%d", &last);
    all.push_back({0, 0, 0b1111, last});
    vector<vector<int>> not_done(k, vector<int>(k, 0b1111));
    for (cond &c : all) {
      if ((not_done[c.id1][c.id2] & c.mask) == 0)
        continue;
      conds.push_back(c);
      not_done[c.id1][c.id2] &= ~c.mask;
      if (not_done[c.id1][c.id2] == 0)
        break;
    }
  }

  vector<int> bits1(k, -1);
  vector<int> bits2(2 * k, -1);
  vector<int> bits3(3 * k, -1);

  auto pw = [](vector<int>& bits) {
    return 1 << count(bits.begin(), bits.end(), -1);
  };

  int ans1 = solve(0, 0, 0, 1, bits1, pw);
  int ans2 = solve(0, 0, k, 1, bits2, [&](vector<int>& b) {
    return solve(0, k, 0, 1, b, pw);
  });
  int ans3 = solve(0, 0, k, 1, bits3, [&](vector<int>& b) {
    return solve(0, k, 2 * k, 1, b, [&](vector<int> &b) {
      return solve(0, 0, 2 * k, 0, b, pw);
    });
  });;


  printf("%d %d %d\n", ans1, ans2, ans3);
  return 0;
}
