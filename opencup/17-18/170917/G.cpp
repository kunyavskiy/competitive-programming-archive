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

const int MOD = int(1e9) + 7;
const int P[2] = {997, int(1e6) + 3};

int sum(int a, int b) {
  a += b;
  if (a >= MOD) {
    a -= MOD;
  }
  return a;
}

int mult(int a, int b) {
  return (int)(ll(a) * b % MOD);
}

void concatHash(ll & hash, int x) {
  int *h = (int*)&hash;
  for (int i = 0; i < 2; ++i) {
    h[i] = sum(mult(h[i], P[i]), x);
  }
}

vector <int> solve1(const vector <ll> & a) {
  int n = int(a.size());
//  eprintf("n %d\n", n);
//  for (int i = 0; i < n; ++i) {
//    eprintf("%lld ", a[i]);
//  }
//  eprintf("\n");
  int M, R;
  M = -1, R = -1;
  vector <int> pal(n, 0);
  for (int i = 1; i < n; ++i) {
    int len;
    if (i <= R) {
      len = min(R - i + 1, pal[2 * M - i]);
    } else {
      len = 0;
    }
    while (i + len < n && i - 1 - len >= 0 && a[i + len] == a[i - 1 - len]) {
      ++len;
    }
    pal[i] = len;
    if (i + len > R) {
      M = i;
      R = i + len - 1;
    }
  }
//  for (int i = 0; i < n; ++i) {
//    eprintf("pal[%d] = %d\n", i, pal[i]);
//  }
//  eprintf("\n");
  vector <int> ends;
  ends.push_back(n - 1);
  for (int i = n - 1; i >= 0; --i) {
    if (i + pal[i] > ends.back()) {
      ends.push_back(i - 1);
    }
  }
  reverse(ends.begin(), ends.end());
//  for (int x : ends) {
//    eprintf("%d ", x);
//  }
//  eprintf("\n");
  return ends;
}

ll solve(vector <ll> & a) {
  vector <int> ends = solve1(a);
  reverse(a.begin(), a.end());
  vector <int> begins = solve1(a);
  reverse(a.begin(), a.end());
  for (auto & x : begins) {
    x = int(a.size()) - 1 - x;
  }
  reverse(begins.begin(), begins.end());
//  eprintf("ends: ");
//  for (int x : ends) {
//    eprintf("%d ", x);
//  }
//  eprintf("\n");
  ll ans = 0;
  for (int i = 0, j = 0; i < int(begins.size()); ++i) {
    while (j < int(ends.size()) && begins[i] > ends[j]) {
      ++j;
    }
//    eprintf("begin %d : %d\n", begins[i], int(ends.size()) - j);
    ans += int(ends.size()) - j;
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector <ll> row(n, 0), col(m, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char x;
      scanf(" %c", &x);
      concatHash(row[i], x);
      concatHash(col[j], x);
    }
  }
  printf("%lld\n", solve(row) * solve(col));
  return 0;
}
