#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <sstream>
//#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME ""

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#ifndef LOCAL
#undef assert
void assert(bool x) {
  if (!x) printf("%d\n", 5 / 0);
}
void assert2(bool x) {
  if (!x) {
    int *tmp = new int[1];
    tmp[int(1e5)] = 100 / 23;
  }
}
#else
#define assert2 assert
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef linux
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

const int inf = 1e9;
const double eps = 1e-9;
const double INF = inf;
const double EPS = eps;

int n;

int readNum() {
  int res = 0;
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; i++) {
    int x;
    scanf("%d", &x), x--;
    res |= 1 << x;
  }
  return res;
}

int main(){     
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  while (scanf("%d", &n) == 1) {
    eprintf("n=%d\n", n);
    int start = readNum();
    int end = readNum();
    vi needEnd;
    for (int i = 0; i < n; i++)
      if (end & (1 << i)) needEnd.pb(i);

    end ^= start;
    vi ord;
    int c0 = 0;
    for (int i = 0; i < n; i++) if (!(end & (1 << i)))
      ord.pb(i), c0++;

    int c1 = 0;
    for (int i = 0; i < n; i++) if (end & (1 << i))
      ord.pb(i), c1++;

    vi ans;

    if (c1 == 0) {
      ans.pb(0);
    } else {
      c1--;
      ans.pb(0);
      ans.pb(1 << (n - 1));

      int coff = 1;
      for (int i = 0; i < c0; i++) {
        vi nans;
        int cur = 0;
        for (int i2 = 0; i2 < sz(ans); i2++) {
          nans.pb(ans[i2] | cur);
          cur ^= coff;
          nans.pb(ans[i2] | cur);
        }
        ans.swap(nans);
        coff <<= 1;
      }
      for (int i = 0; i + 2 <= c1; i += 2) {
        assert(sz(ans) % 2 == 0);

        vi nans;
        for (int i2 = 0; i2 < sz(ans);) {
          nans.pb(ans[i2] | (0 * coff));
          nans.pb(ans[i2] | (1 * coff));
          nans.pb(ans[i2] | (3 * coff));
          nans.pb(ans[i2] | (2 * coff));
          i2++;
          if (i2 + 1 < sz(ans)) {
            nans.pb(ans[i2] | (2 * coff));
            nans.pb(ans[i2] | (3 * coff));
            nans.pb(ans[i2] | (1 * coff));
            nans.pb(ans[i2] | (0 * coff));
          } else {
            nans.pb(ans[i2] | (2 * coff));
            nans.pb(ans[i2] | (0 * coff));
            nans.pb(ans[i2] | (1 * coff));
            nans.pb(ans[i2] | (3 * coff));
          }
          i2++;
        }
        ans.swap(nans);
        coff <<= 2;
      }
      if (c1 % 2) {
        vi nans;
        for (int i2 = 0; i2 < sz(ans);) {
          nans.pb(ans[i2] | (0 * coff));
          nans.pb(ans[i2] | (1 * coff));
          i2++;
          nans.pb(ans[i2] | (1 * coff));
          nans.pb(ans[i2] | (0 * coff));
          i2++;
        }
        nans.pop_back();
        ans.swap(nans);
      }
    }

    for (int i = 1; i < sz(ans); i++) {
      int diff = ans[i - 1] ^ ans[i];
      assert((diff & (diff - 1)) == 0);
    }
    assert(ans[0] == 0);

    printf("%d\n", sz(ans));
    vi last;
    for (int i = 0; i < sz(ans); i++) {
      int y = 0;
      for (int i2 = 0; i2 < n; i2++) if (ans[i] & (1 << i2))
        y |= 1 << ord[i2];

      y ^= start;
      vi res;
      for (int i2 = 0; i2 < n; i2++) if (y & (1 << i2))
        res.pb(i2);
      last = res;

      sort(res.begin(), res.end());
      printf("%d", sz(res));
      for (int i = 0; i < sz(res); i++)
        printf(" %d", res[i] + 1);
      printf("\n");
    }
    assert(last == needEnd);
  }

  TIMESTAMP(end);
  return 0;
}
