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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

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

struct segment {
  int l, r, c, d;
  bool operator<(const segment& r) {
    return l < r.l;
  }
};

vector<segment> s;

const int MAXA_LOG = 10;
const int MAXA = 1 << MAXA_LOG;
const int MOD = 1000210433;
int ans[2 * MAXA];
int cur[2 * MAXA];
int temp1[2 * MAXA];
int temp2[2 * MAXA];

map<pair<vector<int>, vector<int>>, vector<int>> cache;

const int MIN_SIZE = 5;

void add(int* a,int* b,int size) {
  for (int i = 0; i < (1 << size); i++) {
    a[i] += b[i];
    if (a[i] >= MOD) a[i] -= MOD;
  }
}

void sub(int* a,int* b,int size) {
  for (int i = 0; i < (1 << size); i++) {
    a[i] -= b[i];
    if (a[i] < 0) a[i] += MOD;
  }
}


void mult_inner(int* a,int* b,int* res,int size) {
  if (size == MIN_SIZE) {
    for (int i = 0; i < (1 << size); i++)
      for (int j = 0; j < (1 << size); j++)
        res[i + j] = (int) ((res[i + j] + a[i] * 1LL * b[j]) % MOD);
    return;
  }
  mult_inner(a, b, res, size - 1);
  mult_inner(a + (1 << (size - 1)), b + (1 << (size - 1)), res + (1 << size), size - 1);
  int *temp = new int[1 << (size)];
  memset(temp, 0, sizeof(int) * (1 << (size)));
  add(a, a + (1 << (size - 1)), size - 1);
  add(b, b + (1 << (size - 1)), size - 1);
  mult_inner(a, b, temp, size - 1);
  sub(a, a + (1 << (size - 1)), size - 1);
  sub(b, b + (1 << (size - 1)), size - 1);
  sub(temp, res, size);
  sub(temp, res + (1 << (size)), size);
  add(res + (1 << (size - 1)), temp, size);
  delete[] temp;
}

void mult(int *a, int *b, int *c) {
  vector<int> _a(a, a + MAXA);
  vector<int> _b(b, b + MAXA);
  vector<int>& res = cache[make_pair(_a, _b)];
  if (!res.empty()) {
    memcpy(c, &res[0], sizeof(int) * MAXA);
  } else {
    memcpy(temp1, a, sizeof(int) * MAXA);
    memcpy(temp2, b, sizeof(int) * MAXA);

    memset(c, 0, 2 * sizeof(int) * MAXA);
    mult_inner(temp1, temp2, c, MAXA_LOG);
    res = vector<int>(c, c + MAXA);
  }
}

void solve() {
  memset(ans, 0, sizeof(ans));
  ans[0] = 1;
  map<pair<int, int>, int> t;
  for (const auto& seg : s) {
    t[{seg.c, seg.d}] += seg.r - seg.l;
  }

  for (const auto &x : t) {
    memset(cur, 0, sizeof(cur));
    for (int i = x.first.first; i <= x.first.second; i++) {
      cur[i] = 1;
    }
    int d = x.second;

    while (d) {
      if (d & 1) {
        mult(ans, cur, ans);
      }
      mult(cur, cur, cur);
      d >>= 1;
    }
  }
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, A, m;
  scanf("%d%d%d", &n, &A, &m);

  s.push_back({0, n, 0, MAXA - 1});
  solve();

  for (int i = 0; i < m; i++) {
    int ty;
    scanf("%d", &ty);
    if (ty == 2) {
      scanf("%d", &A);
    } else {
      int l, r, c, d;
      scanf("%d%d%d%d", &l, &r, &c, &d);
      --l;
      vector<segment> ns;
      ns.push_back({l, r, c, d});

      for (auto seg : s) {
        if (r <= seg.l || seg.r <= l) {
          ns.push_back(seg);
        } else if (l <= seg.l) {
          if (r < seg.r) {
            seg.l = r;
            ns.push_back(seg);
          }
        } else {
          if (r < seg.r) {
            ns.push_back({seg.l, l, seg.c, seg.d});
            ns.push_back({r, seg.r, seg.c, seg.d});
          } else {
            seg.r = l;
            ns.push_back(seg);
          }
        }
      }
      s = ns;
      sort(s.begin(), s.end());
      solve();
    }
    printf("%d\n", ans[A]);
  }

  return 0;
}
