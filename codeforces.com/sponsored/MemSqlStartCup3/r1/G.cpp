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

const int MAXN = 100000;

map<int, ll> vals[MAXN * 10];
set<int> nz[MAXN];

void set_val(int x, int y, ll val) {
  if (val) {
    vals[x][y] = val;
    nz[y].insert(x);
  } else {
    vals[x].erase(y);
    nz[y].erase(x);
  }
}

char s[MAXN];

void dump(int f, int n, int m) {
  for (int i = f; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%3lld ", vals[i].count(j) ? vals[i][j] : 0);
    }
    printf("\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n;
  scanf("%d%s", &n, s);
  vector<bool> used(n + 1);

  int ptr = 0;

  for (int i = 2; i <= n; i++) {
    if (used[i]) continue;
    for (int j = 2 * i; j <= n; j += i) {
      used[j] = true;
    }
    if (n % i != 0) continue;
    int d = n / i;
    for (int j = 0; j < d; j++) {
      for (int k = j; k < n; k += d) {
        set_val(ptr, k, 1);
      }
      ptr++;
    }
  }
  for (int i = 0; i < n; i++) {
    set_val(ptr, i, s[i] - '0');
  }

  eprintf("ptr = %d\n", ptr);

  int ops1 = 0, ops2 = 0, ops3 = 0;
  for (int i = 0; i < ptr; i++) {
    if (i % 1000 == 0)
      eprintf("i = %d, ptr = %d, ops = %d, ops2 = %d, ops3 = %d\n", i, ptr, ops1, ops2, ops3);
    if (vals[i].empty()) continue;

    int bit = vals[i].begin()->first;
    set<int>::iterator it = nz[bit].begin();
    while (it != nz[bit].end()) {
      int j = *it;
      it++;
      if (j > i) {
        ++ops1;
        ll a = vals[i][bit];
        ll b = -vals[j][bit];
        ll g = __gcd(abs(a), abs(b));
        a /= g;
        b /= g;
        if (a == -1) {
          a = -a;
          b = -b;
        }
        if (a != 1) {
          for (auto &x : vals[j]) {
            x.second *= a;
            ++ops2;
          }
        }
        for (auto x : vals[i]) {
          ++ops3;
          set_val(j, x.first, vals[j][x.first] + x.second * b);
        }
        assert(vals[j].count(bit) == 0);
      }
    }
//    dump(0, ptr + 1, n);
//    printf("\n\n\n");
  }

  printf("%s\n", vals[ptr].empty() ? "YES" : "NO");

  return 0;
}
