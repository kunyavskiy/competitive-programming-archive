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
#include <unordered_map>
#include <random>

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


const int SZ = 2.5e8;
char buf[SZ];
int csz = 0;

void* operator new(size_t sz) {
  assert(csz + sz < SZ);
  void* res = buf + csz;
  csz += sz;
  return res;
}

void operator delete(void*) {}
void operator delete(void*, size_t) {}


typedef long long ll;
typedef long double ld;

ll T = 1000000;

mt19937 rnd;
ll read() {
  //return (rnd() | ((ll)rnd() << 30)) % (ll)1e11;
  double x;
  scanf("%lf", &x);
  return (ll)round(x * T);
}

struct fenwick {
  ll n;
  unordered_map<ll, ll> f;

  fenwick(ll _n) {
    n = _n;
    f.reserve(4.5e6);
  }
  void add(ll x, ll y) {
    for (; x < n; x |= x + 1) {
      f[x] += y;
    }
  }
  ll get(ll x) {
    ll res = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) {
      auto it = f.find(x);
      if (it != f.end()) res += it->second;
      //res += f[x];
    }
    return res;
  }
  ll get(ll l, ll r) {
    return get(r) - get(l - 1);
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  scanf("%d", &n);
  //n = 1e5;

  ll maxC = n * T;
  ll csum = 0;
  int ids = 0;

  fenwick f0(maxC + 1), f1(maxC + 1);
  for (int i = 0; i < 2 * n; i++) {
    //if (i % 10000 == 0) cerr << i << endl;

    int tp;
    scanf("%d", &tp);
    //tp = i % 2;
    if (tp == 0) {
      int id = ids++;
      ll c, r;
      c = read();
      r = read();
      c = (c + (__int128)csum * T) % maxC;
      ll L = max(0LL, c - r);
      ll R = min(maxC, c + r);

      f1.add(L, +id);
      f0.add(L, +1);
      f1.add(R + 1, -id);
      f0.add(R + 1, -1);
    } else {
      ll x = read();
      x = (x + (__int128)csum * T) % maxC;

      ll res = f0.get(x);
      printf("%lld\n", res);
      csum += f1.get(x);
    }
  }
  //cerr << csz << endl;

  return 0;
}
