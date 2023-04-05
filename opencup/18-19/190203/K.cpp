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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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

int n;
vector<ll> a[2];
//unordered_map<ll,ll> mem;
ll mem[pw(11)][pw(11)];


vector<ll> smask[2];

ll rec(int m0, int m1) {
//  ll h = (m0 * pw(11)) + m1;


  if (mem[m0][m1] != -1) {
    return mem[m0][m1];
  }
//  if (mem.count(h) != 0) {
//    return mem[h];
//  }
    //  db3(m0, m1, id);
  int m[2] = {m0, m1};
  if (m[0] == m[1] && m[0] == pw(n) - 1) {
    return 0;
  }
  ll s0 = smask[0][m0];
  ll s1 = smask[1][m1];
  int type = (s0 > s1)? 0: 1;
  ll add = abs(s0 - s1);
  ll best_res = 0;
//  db(n);
  for (int i = 0; i < n; i++) {
    if ((m[type ^ 1] & pw(i)) == 0) {
      int nm[2];
      nm[0] = m[0];
      nm[1] = m[1];
      nm[type ^ 1] ^= pw(i);
      best_res = max(best_res, rec(nm[0], nm[1]));
    }
  }

  for (int i = 0; i < n; i++) {
    if ((m[0] & pw(i)) == 0 && (m[1] & pw(i)) == 0) {
      ll R = min(a[type][i] + add, a[type ^ 1][i]);
      ll L = add;
      ll tmp = max(0ll, R - L);
      ll nm[2];
      nm[0] = m[0] ^ pw(i);
      nm[1] = m[1] ^ pw(i);

      best_res = max(best_res, rec(nm[0], nm[1]) + tmp);
    }
  }


  mem[m0][m1] = best_res;
//  if (mem.size() % 100000 == 0) {
//    db(mem.size());
//  }
  return best_res;
}


int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
//  freopen("k.out", "w", stdout);
#endif
  scanf("%d", &n);
  a[0].resize(n);
  a[1].resize(n);
  ll s0 = 0;
  ll s1 = 0;
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &a[0][i], &a[1][i]);
//    a[0][i] = rand() % 10000;
//    a[1][i] = rand() % 10000;
    s0 += a[0][i];
    s1 += a[1][i];
  }
  for (int i = 0; i < n; i++) {
    a[0][i] *= s1;
    a[1][i] *= s0;
  }
  memset(mem, -1, sizeof mem);


  for (int tt = 0; tt < 2; tt++) {
    smask[tt].resize(pw(n));
    for (int mask = 0; mask < pw(n); mask++) {
      ll s = 0;
      for (int i = 0; i < n; i++) {
        s += a[tt][i] * ((mask >> i) & 1);
      }
      smask[tt][mask] = s;
    }
  }


  ll ans = 0;
  for (int i = 0; i < n; i++) {
//    ans = max(rec(pw(i), 0, i, 0, a[0][i]), ans);
    ans = max(rec(0, 0), ans);
  }
//  db(mem.size());
  printf("%.17f\n", ans * 1.0 / (s0 * s1));


  return 0;
}
