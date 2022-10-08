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

bool rat_less(ll a, ll b, ll c, ll d) {
  if (a / b != c / d) {
    return a / b < c / d;
  }
  a %= b;
  c %= d;
  if (a == 0 || c == 0) {
    return a == 0 && c != 0;
  }
  return !rat_less(b, a, d, c);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    vector<int> b(n);
    ll score = 0;
    vector<int> pens;
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &a[i], &b[i]);
      if (a[i] < b[i]) {
        score += b[i] - a[i];
        pens.push_back(b[i]); // + b[i] - a[i] -> -a[i]
      } else {
        pens.push_back(a[i]);
      }
      eprintf("%d[%d %d]\n", pens[i], a[i], b[i]);
    }
    eprintf("\n");
    eprintf("score = %lld\n", score);
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
      order[i] = i;
    }
    sort(order.begin(), order.end(), [&](int a, int b) {
      return pens[a] < pens[b];
    });

    ll ans_num = 0;
    ll ans_den = 1;



    auto upd = [&](ll num, ll den) {
      ll g = __gcd(num, den);
      num /= g;
      den /= g;
      eprintf("%lld %lld %.18lf\n", num, den, num * 1.0 / den);
      if (rat_less(ans_num, ans_den, num, den)) {
        ans_num = num;
        ans_den = den;
      }
    };

    for (int i_ = 0; i_ < n; i_++) {
      int i = order[i_];
      if (score >= pens[i]) {
        score -= pens[i];
      } else {
        upd(i_, n);
        for (int j_ = 0; j_ < n; j_++) {
          ll rscore = score;
          int j = order[j_];
          if (j_ < i_) {
            rscore += pens[j];
            rscore -= pens[i];
          }
          if (rscore < 0) continue;
          if (a[j] < b[j]) {
            assert(pens[j] == b[j]);
            // b[i] * a >= score - b[j]
            ll extra_num = rscore;
            assert(extra_num < pens[j]);
            if (extra_num > 0) {
              upd(i_ * 1LL * pens[j] + extra_num, n * 1LL * pens[j]);
            }
          } else {
            assert(a[j] > rscore);
            // b[i] * a >= a[i] - score
            // i * n + (b[i] - a[i] + score) / b[i]
            if (b[j] >= a[j] - rscore) {
              upd(i_ * 1LL * b[j] + (b[j] - a[j] + rscore), n * 1LL * b[j]);
            }
          }
        }
        break;
      }
    }
    printf("%lld %lld\n", ans_num, ans_den);
  }


  return 0;
}
