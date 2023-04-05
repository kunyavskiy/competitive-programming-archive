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
#include <numeric>
#include <unordered_map>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define CHECK

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

struct value {
  ll sum;
//  vector<int> cnt;
//  ll sum2;
  ll sum3;
  explicit value(int k  __attribute__((unused)) = 0) {
    sum = sum3 = 0;
//    cnt = vector<int>(k);
  }
};

struct state {
  int k, a, d, m;
  bool top;

  bool operator==(const state &rhs) const {
    return k == rhs.k &&
           a == rhs.a &&
           d == rhs.d &&
           m == rhs.m &&
           top == rhs.top;
  }
};

namespace std {
#define MAGIC 6985542118606559583ULL
  template <>
  struct hash<state> {
    size_t operator()(const state& s) const {
      return (((s.k * MAGIC + s.a) * MAGIC + s.d) * MAGIC + s.m) * MAGIC + s.top;
    }
  };
}

unordered_map<state, value> cache;

value solve(int k, int a, int d, int m, bool top) {
  assert(m > 0);
  state s{k, a, d, m, top};
  auto it = cache.find(s);
  if (it != cache.end()) {
    return it->second;
  }
  value &res = cache[s];

  value lf, rg;
  int pos = (1 << (k - 1)) - 2;
  int pos2;
  if (top) {
    pos2 = pos + 1;
  } else {
    pos2 = pos;
  }
  int last = a + d * (m - 1);
  assert(last < (1 << k) - 2);

  int before;
  if (a <= pos2) {
    before = (pos2 - a) / d + 1;
  } else {
    before = 0;
  }
  int after;
  if (last == (1 << k) - 3 && !top) {
    after = 1;
  } else {
    after = 0;
  }

  if (a < pos) {
    lf = solve(k - 1, a, d, min(m, (pos - 1 - a) / d + 1), false);
    lf.sum += lf.sum3;
    lf.sum3 *= 2;
  } else {
    lf = value(k);
  }
  if (last > pos2 && m != before + after) {
    rg = solve(k - 1, a + before * d - pos2 - 1, d, m - before - after, top);
    rg.sum3 *= 2;
    rg.sum += rg.sum3;
  } else {
    rg = value(k);
  }

  res = lf;
  res.sum += rg.sum;
  res.sum3 += rg.sum3;

  if (pos >= a && pos <= last && (pos - a) % d == 0) {
    res.sum += 1;
    res.sum3 += 1;
  }
  if (top) {
    if (pos2 >= a && pos2 <= last && (pos2 - a) % d == 0) {
      res.sum += 3;
      res.sum3 += 2;
    }
  } else {
    pos2 = (1 << k) - 3;
    if (pos2 >= a && pos2 <= last && (pos2 - a) % d == 0) {
      res.sum += 1;
      res.sum3 += 1;
    }
  }

  return res;
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int k, q;
  scanf("%d%d", &k, &q);

  for (int i = 0; i < q; i++) {
    cache.rehash(200000);
    int a, d, m;
    scanf("%d%d%d", &a, &d, &m);
    value res = solve(k, a - 1, d, m, true);
    printf("%lld\n", res.sum);
//    eprintf("%d\n", (int)cache.size());
    cache.clear();
//    fflush(stdout);
  }

  return 0;
}
