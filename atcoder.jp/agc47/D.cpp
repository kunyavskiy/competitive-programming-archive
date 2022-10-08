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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int h;
  while (scanf("%d", &h) == 1) {
    --h;
    int L = 1 << h;
    vector<int> prods(2 * L);
    vector<int> iprods(2 * L);
    prods[1] = 1;
    iprods[1] = 1;
    for (int i = 2; i < 2 * L; i++) {
      prods[i] = mul(prods[i / 2], i);
      iprods[i] = mul(i, minv(mul(prods[i], prods[i])));
    }
    vector<int> tree(2 * L);
    auto set = [&](int pos, int val) {
      pos += L;
      tree[pos] = val;
      while (pos /= 2) {
        tree[pos] = tree[2 * pos];
        add(tree[pos], tree[2 * pos + 1]);
      }
    };

    vector<int> p(L);
    for (int i = 0; i < L; i++) {
      scanf("%d", &p[i]);
      --p[i];
    }

    int ans = 0;

    function<void(int, int)> solve = [&](int l, int r) {
      if (r - l == 1) return;
      int m = (l + r) / 2;
      solve(l, m);
      solve(m, r);
      for (int i = m; i < r; i++) {
        set(p[i], mul(prods[i + L], prods[p[i] + L]));
      }
      int ll = l + L, rr = r + L - 1;
      while (ll != rr) {
        ll /= 2;
        rr /= 2;
      }
      for (int i = l; i < m; i++) {
        int cur = mul(iprods[ll], mul(prods[i + L], prods[p[i] + L]));
        int t = p[i] + L;
        while (t != 1) {
          int other = mul(tree[t ^ 1], iprods[t / 2]);
          add(ans, mul(cur, other));
          t /= 2;
        }
      }
      for (int i = m; i < r; i++) {
        set(p[i], 0);
      }
    };
    solve(0, L);
    printf("%d\n", ans);
  }

  return 0;
}
