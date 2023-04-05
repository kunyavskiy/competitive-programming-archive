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
#include <unordered_set>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

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
typedef unsigned long long ull;
typedef long double ld;

#define bit(x, y) (1ULL << (x * 8 + y))

int bit_out[8];
int bit_in[8];

ull forbidden;

set<ull> ans_s;

void solve2(ull mask, ull es) {
  if (!ans_s.insert(es).second) {
    return;
  }

  vector<int> v;
  for (int i = 0; i < 7; i++) {
    if (mask & (1 << i)) {
      v.push_back(i);
    }
  }

  for (int i : v) {
    for (int j : v) {
      if (!(es & bit(i, j))) {
        ll nes = es | bit(i, j);
        for (int k : v) {
          if (es & (bit(k, i))) {
            for (int l : v) {
              if (es & bit(j, l)) {
                nes |= bit(k, l);
              }
            }
          }
        }
        if (nes & forbidden) {
          continue;
        }
        solve2(mask, nes);
      }
    }
  }
}

int solve2(ll mask) {
  static map<int, int> cache;

  int sz = __builtin_popcount(mask);

  if (cache.find(sz) != cache.end()) {
    return cache[sz];
  }

  eprintf("solve for sz = %d\n", sz);

  ans_s.clear();
  ull start = 0;
  for (int i = 0; i < 7; i++) {
    if (mask & (1 << i)) {
      start |= bit(i, i);
    }
  }
  solve2(mask, start);
  cache[sz] = ans_s.size();
  eprintf("res for sz = %d\n", cache[sz]);
  return cache[sz];
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  int n, k;
  scanf("%d %d", &k, &n);
  vector<int> v(n);
  for (int &x: v) scanf("%d", &x);

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      bit_out[i] |= bit(i, j);
      bit_in[j] |= bit(i, j);
    }
  }


  for (int x : v) {
    for (int i = 0; i < k; i++) {
      for (int j = 0; j < k; j++) {
        if ((x & (1 << i)) && !(x & (1 << j))) {
          forbidden |= bit(i, j);
        }
      }
    }
  }


  int all = (1 << k) - 1;
  int and_all = (1 << k) - 1, or_all = 0;
  for (int x : v) {
    and_all &= x;
    or_all |= x;
  }

  int zeros = all ^ or_all;
  int ones = and_all;

  int normal = all ^ zeros ^ ones;

  int ans = 0;
  if (zeros == all && ones == all) {
    normal = 0;
    ans++;
  }

  for (int mask = normal;; mask = (mask + 1) | normal) {
    int res = solve2(mask);
    if (zeros == all && ones == all) {
      ans += res * (1 << __builtin_popcount(all ^ mask));
    } else {
      ans += res;
    }
    if (mask == all) break;
  }

  printf("%d\n", ans);

  return 0;
}
