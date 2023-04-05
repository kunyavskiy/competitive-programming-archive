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
typedef long double ld;

struct item {
  int p[4]{};
  int& operator[](int x) { return p[x];}
  const int& operator[](int x) const { return p[x];}
  bool operator==(const item &rhs) const { return memcmp(p, rhs.p, sizeof(int)*4) == 0; }
  bool operator!=(const item &rhs) const { return !(rhs == *this); }
};

item operator*(const item&a, const item&b) {
  item res;
  for (int i = 0; i < 4; i++) {
    res[i] = a[b[i]];
  }
  return res;
}

item operator~(const item &a) {
  item res;
  for (int i = 0; i < 4; i++) {
    res[a[i]] = i;
  }
  return res;
}


char buf[(1 << 20) + 10];

int v[24][24];
int neg[24];
int ids[3];

void precalc() {
  const item a{{0, 2, 3, 1}};
  const item c{{1, 0, 2, 3}};
  const item b = ~(c * a);

  const item e{{0, 1, 2, 3}};

  assert(a * a == b * c);
  assert(b * b * b == c * a);
  assert(c * c  == e);
  assert(a * b * c == e);

  vector<item> is;
  item cur = e;
  do {
    is.push_back(cur);
  } while (next_permutation(cur.p, cur.p + 4));

  auto conv = [&](const item&a) {
    int pos =  find(begin(is), end(is), a) - is.begin();
    assert(pos < (int)size(is));
    return pos;
  };


  for (int i = 0; i < 24; i++) {
    neg[i] = conv(~is[i]);
    for (int j = 0; j < 24; j++) {
      v[i][j] = conv(is[i] * is[j]);
    }
  }

  ids[0] = conv(a);
  ids[1] = conv(b);
  ids[2] = conv(c);
}

void solve() {
  int n, m;

  scanf("%d%d", &n, &m);

  int cnts[24];
  ll ans[24];
  memset(cnts, 0, sizeof(cnts));
  memset(ans, 0, sizeof(ans));

  scanf("%s", buf);
  int res = 0;
  cnts[res]++;
  for (int i = 0; buf[i]; i++) {
    res = v[res][ids[buf[i] - '0']];
    for (int j = 0; j < 24; j++) {
      ans[v[j][res]] += cnts[j];
    }
    cnts[neg[res]]++;
  }
  auto read_string = [&]() {
    scanf("%s", buf);
    int res = 0;
    for (int i = 0; buf[i]; i++) {
      res = v[res][ids[buf[i] - '0']];
    }
    return res;
  };

  for (int i = 0; i < m; i++) {
    int val = read_string();
    printf("%lld\n", ans[val]);
  }
}

int main() {
  precalc();
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();

  return 0;
}
