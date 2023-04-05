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

#define TASKNAME "A"

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

const long long INF = (long long)1.1e18;
const int MAXN = 1000100;
const int TSIZE = (1 << 22);

struct item {
  int sum, minp;

  item(int sum, int minp) : sum(sum), minp(minp) {}
  item() : sum(0), minp(0) {}
};

item merge(const item& a, const item& b) {
  return item(a.sum + b.sum, min(a.minp, a.sum + b.minp));
}

int cycle_len;
int a[MAXN];
int order[2*MAXN];
char s[MAXN];
int spos[MAXN];

int lst;
item tree[TSIZE];


//#define TEST

item get(int v, int l, int r, int L, int R) {
  if (r <= L || R <= l) return item(0, 0);
  if (L <= l && r <= R) {
    return tree[v];
  }
  item lv = get(2*v, l, (l+r)/2, L, R);
  item rv = get(2*v+1, (l+r)/2, r, L, R);
  return merge(lv, rv);
}

pair<item, int> get_first(int v, int l, int r, int L, int R, int value) {
  if (r <= L || R <= l) return mp(item(0, 0), -1);
  if (L <= l && r <= R) {
    if (value + tree[v].minp <= 0) {
      while (v < lst) {
        if (value + tree[2 * v].minp <= 0) {
          v = 2 * v;
        } else {
          value += tree[2 * v].sum;
          v = 2 * v + 1;
        }
      }
      return make_pair(tree[v], v - lst - L);
    } else {
      return make_pair(tree[v], -1);
    }
  }
  auto lv = get_first(2*v, l, (l+r)/2, L, R, value);
  if (lv.second != -1) {
    return lv;
  }
  auto rv = get_first(2*v+1, (l+r)/2, r, L, R, value + lv.first.sum);
  if (rv.second != -1) {
    return rv;
  }
  return make_pair(merge(lv.first, rv.first), -1);
}


item get_sum_minp(int l, int r) {
  #ifdef TEST
  int sum2 = 0;
  int minp2 = 0;
  for (int i = l; i < r; i++) {
    sum2 += order[i];
    minp2 = min(minp2, sum2);
  }
  #endif
  item ans = get(1, 0, lst, l, r);
  #ifdef TEST
  assert(sum2 == ans.sum);
  assert(minp2 == ans.minp);
  #endif
  return ans;
}

int get_minp_first(int l, int r, int value) {
  #ifdef TEST
  int sum2 = 0;
  int ans2 = -1;
  for (int i = l; i < r; i++) {
    sum2 += order[i];
    if (value + sum2 <= 0) {
      ans2 = i - l;
      break;
    }
  }
  assert(ans2 != -1);
  #endif
  int ans = get_first(1, 0, lst, l, r, value).second;
  #ifdef TEST
  assert(ans == ans2);
  #endif
  return ans;
}


long long solve(int value, int start) {
  item sum_minp = get_sum_minp(start, start + cycle_len);
  int sum = sum_minp.sum;
  int minp = -sum_minp.minp;

  long long cycles;
  if (sum >= 0) {
    if (value > minp) {
      return INF;
    }
    cycles = 0;
  } else {
    cycles = ((value - minp - sum - 1) / -sum);
    if (cycles < 0) {
      cycles = 0;
    }
  }
  long long ans = cycle_len * 1LL * cycles;
  value += cycles * sum;
  assert(value <= minp);

  return ans + get_minp_first(start, start + cycle_len, value);
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  int m;
  scanf("%d",&m);
  scanf("%s", s);

  int g = __gcd(n, m);
  cycle_len = m / g;

  int ptr = 0;
  for (int i = 0; i < g; i++) {
    int pos = i;
    for (int k = 0; k < 2 *cycle_len; k++) {
      pos = (pos + n) % m;
      if (k < cycle_len) {
        spos[pos] = ptr;
      }
      if (s[pos] == 'W') {
        order[ptr++] = 1;
      } else {
        order[ptr++] = -1;
      }
    }
  }

  lst = 2;
  while (lst < ptr) {
    lst *= 2;
  }

  for (int i = 0; i < ptr; i++) {
    tree[i + lst] = item(order[i], min(order[i], 0));
  }

  for (int i = lst - 1; i >= 0; i--) {
    tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
  }

  long long ans = INF;

  for (int i = 0; i < n; i++) {
    long long cnt = solve(a[i], spos[i % m]);
    if (cnt != INF) {
      ans = min(ans, cnt * n + i + 1);
    }
  }


  if (ans == INF) {
    printf("-1\n");
  } else {
    printf("%lld\n", ans);
  }

  return 0;
}
