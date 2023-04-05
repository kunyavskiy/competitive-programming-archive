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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

typedef unsigned long long ll;
typedef long double ld;

ll big_bit(ll x) {
  return 1ull << (63u - __builtin_clzll(x));
}

void solve() {
  ll v = 0;
  int n, m;
  scanf("%d%d", &n, &m);
  auto read_vector = [&] (int n){
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
      ll x, y;
      scanf("%llu%llu", &x, &y);
      v ^= x;
      a[i] = x ^ y;
    }
    vector<ll> base;
    for (int i = 0; i < n; i++) {
      if (a[i] != 0) {
        ll bit = big_bit(a[i]);
        for (ll &b : base) {
          if (b & bit) {
            b ^= a[i];
          }
        }
        base.push_back(a[i]);
        for (int j = i + 1; j < n; j++) {
          if (a[j] & bit) {
            a[j] ^= a[i];
          }
        }
      }
    }
    return base;
  };
  vector<ll> a = read_vector(n);
  vector<ll> b = read_vector(m);

  vector<ll> inv_b;
  for (ll bit = (1ull << 59u); bit > 0; bit /= 2) {
    bool found = false;
    ll vals = bit;
    for (ll x : b) {
      ll bb = big_bit(x);
      if (bb == bit) {
        found = true;
      } else if (x & bit) {
        assert(bb > bit);
        vals ^= bb;
      }
    }
    if (!found) {
      inv_b.push_back(vals & ~(bit - 1));
    }
  }

  vector<ll> na;
  for (ll mask : inv_b) {
    ll value = 0;
    for (ll x : a) {
      if (__builtin_parityll(x & mask)) {
        value = x;
      }
    }
    if (!value) {
      continue;
    }
    a.erase(find(a.begin(), a.end(),value));
    for (ll &x : a) {
      if (__builtin_parityll(x & mask)) {
        x ^= value;
        assert(!__builtin_parityll(x & mask));
      }
    }
    if (!__builtin_parityll(v & mask)) {
      v ^= value;
    }
  }

  for (ll x : b) {
    if (v & big_bit(x)) {
      v ^= x;
    }
  }

  printf("%llu\n", v);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
