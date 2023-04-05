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

typedef __int128_t ll;
typedef long double ld;

ll next() {
  int x;
  scanf("%d", &x);
  return x;
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> fun(n);
    for (int i = 0; i < n; i++) {
      char s[5];
      scanf("%s", s);
      for (int j = 0; j < 4; j++) {
        if (s[j] == '1') {
          fun[i] |= (1 << j);
        }
      }
    }
    vector<ll> a(1 << n), b(1 << n);
    for (ll &v : a) { v = next(); }
    for (ll &v : b) { v = next(); }

    auto do_trans_bit = [&](vector<ll> &a, int b, auto fun) {
      for (int i = 0; i < (1 << n); i++) {
        if (i & (1 << b)) {
          fun(a[i ^ (1 << b)], a[i]);
        }
      }
    };

    auto inv_bit = [&](vector<ll> &a, int b) {
      do_trans_bit(a, b, [](ll &x, ll &y) { swap(x, y); });
    };
    auto clean_bit = [&](vector<ll> &a, int b) {
      do_trans_bit(a, b, [](ll &x, ll &y) {
        x += y;
        y = 0;
      });
    };

    vector<bool> inv_ans(n);
    vector<bool> is_xor(n);
    for (int i = 0; i < n; i++) {
      if (fun[i] & 1) {
        inv_ans[i] = !inv_ans[i];
        fun[i] = fun[i] ^ 15;
      }
      switch (fun[i] / 2) {
        case 0: clean_bit(a, i); clean_bit(b, i); break;
        case 1: inv_bit(b, i); inv_ans[i] = !inv_ans[i]; break;
        case 2: inv_bit(a, i); inv_ans[i] = !inv_ans[i]; break;
        case 3: is_xor[i] = true; break;
        case 4: inv_bit(a, i); inv_bit(b, i); inv_ans[i] = !inv_ans[i]; break;
        case 5: clean_bit(a, i); break;
        case 6: clean_bit(b, i); break;
        case 7: break;
      }
    }

    auto adamar = [](ll &x, ll &y) {
      ll t = x - y;
      x = x + y;
      y = t;
    };
    auto or_t = [](ll &x, ll &y) {
      y += x;
    };

    for (int i = 0; i < n; i++) {
      if (is_xor[i]) {
        do_trans_bit(a, i, adamar);
        do_trans_bit(b, i, adamar);
      } else {
        do_trans_bit(a, i, or_t);
        do_trans_bit(b, i, or_t);
      }
    }

    vector<ll> c(1 << n);
    for (int i = 0; i < (1 << n); i++) {
      c[i] = a[i] * b[i];
    }
    for (int i = 0; i < n; i++) {
      if (is_xor[i]) {
        do_trans_bit(c, i, adamar);
        for (ll &v : c) {
          assert(v % 2 == 0);
          v /= 2;
        }
      } else {
        do_trans_bit(c, i, [](ll &x, ll &y) {
          y -= x;
        });
      }
    }
    for (int i = 0; i < n; i++) {
      if (inv_ans[i]) {
        inv_bit(c, i);
      }
    }

    for (ll &v : c) {
      printf("%ld ", (int64_t)v);
    }
    printf("\n");
  }

  return 0;
}
