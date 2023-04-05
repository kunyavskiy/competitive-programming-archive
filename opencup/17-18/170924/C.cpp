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
typedef pair<int,int> pii;

const int MAGIC = 5;

vector <bool> on;
vector <bool> is_small;
vector <vector<pii>> cnt, cnt_big;
vector <int> cnt_zeroes, cnt_ones;

int get_count(int col) {
  int res = 0;
  if (is_small[col]) {
    for (auto p : cnt[col]) {
      if (on[col] != on[p.first]) {
        res += p.second;
      }
    }
  } else {
    res = on[col] ? cnt_zeroes[col] : cnt_ones[col];
  }
  eprintf("get_count %d\n", res);
  return res;
}

void invert(int col) {
  for (auto p : cnt_big[col]) {
    if (on[col]) {
      cnt_ones[p.first] -= p.second;
      cnt_zeroes[p.first] += p.second;
    } else {
      cnt_ones[p.first] += p.second;
      cnt_zeroes[p.first] -= p.second;
    }
//    eprintf("%d: %d %d\n", p.first, cnt_zeroes[p.first], cnt_ones[p.first]);
  }
  on[col] = !on[col];

}

#define GEN 0

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, k, q;
#if GEN
  int seed = 16468613;
  srand(seed);
  n = 100;
  k = n;
  q = 200000;
#else
  scanf("%d%d%d", &n, &k, &q);
#endif
  vector <int> a(n + 2, 0);
  for (int i = 1; i <= n; ++i) {
#if GEN
    a[i] = rand() % k + 1;
#else
    scanf("%d", &a[i]);
#endif
  }
  ++k;
  n += 2;
  vector <vector<int>> neigh(k);
  for (int i = 0; i < n; ++i) {
    if (i) {
      neigh[a[i]].push_back(a[i - 1]);
    }
    if (i + 1 < n) {
      neigh[a[i]].push_back(a[i + 1]);
    }
  }
  cnt.resize(k);
  for (int i = 0; i < k; ++i) {
    sort(neigh[i].begin(), neigh[i].end());
    for (int j = 0; j < int(neigh[i].size()); ++j) {
      if (j == 0 || neigh[i][j] != neigh[i][j - 1]) {
        cnt[i].push_back({neigh[i][j], 0});
      }
      cnt[i].back().second += 1;
    }
  }
  is_small.assign(k, false);
  for (int i = 0; i < k; ++i) {
    is_small[i] = (int(cnt[i].size()) < MAGIC);
  }
  cnt_zeroes.assign(k, 0);
  cnt_ones.assign(k, 0);
  cnt_big.resize(k);
  for (int i = 0; i < k; ++i) {
    eprintf("%d:", i);
    for (auto p : cnt[i]) {
      eprintf(" (%d,%d)", p.first, p.second);
      if (!is_small[p.first]) {
        cnt_big[i].push_back(p);
        cnt_zeroes[p.first] += p.second;
      }
    }
    eprintf("\n");
  }

  on.assign(k, false);
  int res = 0;
  for (int i = 0; i < q; ++i) {
    int col;
#if GEN
    col = rand() % (k - 1) + 1;
#else
    scanf("%d", &col);
#endif
    res -= get_count(col);
    invert(col);
    res += get_count(col);
    eprintf("2*res = %d\n", res);
    assert(res % 2 == 0);
    printf("%d\n", res / 2);
    fflush(stdout);
  }

  return 0;
}
