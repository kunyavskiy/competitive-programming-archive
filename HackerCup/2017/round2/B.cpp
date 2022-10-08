//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;


long long int get_prev(const map<int, int> &s, map<int, int>::iterator it) {
  if (it == s.begin() || it == s.end()) return 0;
  auto nit = it;
  nit--;
  long long d = it->first - nit->first;
  long long h1 = it->second;
  long long h2 = nit->second;
  assert((h1 + h2) % 2 == 0);
  long long hm = (h1 + h2) / 2;
  return hm * d;
}

long long int get_next(const map<int, int> &s, map<int, int>::iterator it) {
  if (it == s.end()) return 0;
  it++;
  return get_prev(s, it);
}

void insert(map<int, int> &s, long long &cur, int x, int h) {
  auto it = s.lower_bound(x);
  assert(it->first != x);
  cur -= get_prev(s, it);
  s[x] = h;
  it = s.find(x);
  cur += get_prev(s, it);
  cur += get_next(s, it);
}

void erase(map<int, int> &s, long long &cur, int x) {
  auto it = s.find(x);
  assert(it != s.end());
  cur -= get_prev(s, it);
  cur -= get_next(s, it);
  auto nit = it;
  nit++;
  s.erase(it);
  cur += get_prev(s, nit);
}

int sign(int x) {
  if (x > 0) return 1;
  if (x == 0) return 0;
  return -1;
}

int get_cur_h(map<int, int> & s, int x) {
  auto it = s.lower_bound(x);
  if (it->first == x) return it->second;
  if (it == s.end()) return 0;
  if (it == s.begin()) return 0;
  auto nit = it;
  nit--;
  return nit->second + (x - nit->first) * sign(it->second - nit->second);
}

void add(map<int, int> &s, long long &cur, int x, int h) {
  if (get_cur_h(s, x) >= h) {
    return;
  }

//  eprintf("%d %d\n", x, h);

  int lrm, rrm;

  if (get_cur_h(s, x - h) == 0) {
    lrm = x - h;
  } else {
    int l = x - h;
    int r = x;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (get_cur_h(s, m) > h - (x - m)) {
        l = m;
      } else {
        r = m;
      }
    }
    lrm = r;
  }

  if (get_cur_h(s, x + h) == 0) {
    rrm = x + h;
  } else {
    int l = x;
    int r = x + h;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (get_cur_h(s, m) > h - (m - x)) {
        r = m;
      } else {
        l = m;
      }
    }
    rrm = l;
  }

  while (true) {
    auto it = s.lower_bound(lrm);
    if (it == s.end() || it->first > rrm) break;
    erase(s, cur, it->first);
  }

  insert(s, cur, x, h);
  insert(s, cur, lrm, h - (x - lrm));
  insert(s, cur, rrm, h - (rrm - x));
}

void solve() {
  int x1, ax, bx, cx;
  int h1, ah, bh, ch;
  int n;
  scanf("%d", &n);
  scanf("%d%d%d%d", &x1, &ax, &bx, &cx);
  scanf("%d%d%d%d", &h1, &ah, &bh, &ch);
  map<int, int> s;

  double ans = 0;
  long long cur = 0;

  for (int i = 0; i < n; i++) {
    add(s, cur, 4*x1, 4*h1);
    ans += cur / 16.0;
//    eprintf("%lld: %lld.%02lld\n", cur, cur / 16, ((cur / 4) % 4) * 25);
    assert(cur % 4 == 0 && cur >= 0);
    x1 = (int) ((x1 * 1LL * ax + bx) % cx + 1);
    h1 = (int) ((h1 * 1LL * ah + bh) % ch + 1);
//    for (auto x : s) {
//      eprintf("%d:%d ", x.first, x.second);
//    }
//    eprintf("\n");
  }

  printf("%.2lf\n", ans);
  fflush(stdout);
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}
