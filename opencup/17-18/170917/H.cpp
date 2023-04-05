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

//ll P = ll(1e13) + 37;
ll P = ll(1e18) + 3;
ll mult(ll a, ll b) {
  ll z = ll(((long double)(a) * b) / P);
  ll res = (a * b - z * P) % P;
  if (res < 0) {
    res += P;
  }
  return res;

//  ll res = 0;
//  while (b) {
//    if (b & 1) {
//      res += a;
//      if (res >= P) {
//        res -= P;
//      }
//    }
//    b /= 2;
//    a *= 2;
//    if (a >= P) {
//      a -= P;
//    }
//  }
//  return res;
}

ll power(ll a, ll n) {
  ll b = 1;
  while (n) {
    if (n & 1) {
      b = mult(a, b);
    }
    a = mult(a, a);
    n /= 2;
  }
  return b;
}

ll inverse(ll x) {
  return power(x, P - 2);
}

const ll MOD = ll(1e9) + 7;

const int MAX = 70100;
double logI[MAX];
double logFact[MAX];
ll inv[MAX];
ll fact[MAX], invFact[MAX];

inline int gcd(int a, int b) {
  while (b) {
    int c = a % b;
    a = b;
    b = c;
  }
  return a;
}

void solve() {
  int tot = 0;
  vector <int> dig(10);
  for (int i = 0; i < 10; ++i) {
    scanf("%d", &dig[i]);
    tot += dig[i];
  }
  ll K;
  scanf("%lld", &K);
  double logCntTot = logFact[tot];
  for (int i = 0; i < 10; ++i) {
    logCntTot -= logFact[dig[i]];
  }
  double logK = log(K + 0.0) + 0.5;
  //eprintf("K %lld logK %.6lf logCntTot %.6lf\n", K, logK, logCntTot);
  ll ans = 0;
  while (tot) {
    int i = 0;
    while (!dig[i]) {
      ++i;
    }
    double newLogCntTot = logCntTot - logI[tot] + logI[dig[i]];
    if (newLogCntTot > logK) {
      --tot;
      --dig[i];
      logCntTot = newLogCntTot;
      ans = (ans * 10 + i) % MOD;
      continue;
    } else {
      break;
    }
  }

//  eprintf("tot %d fact[tot] %lld\n", tot, fact[tot]);
  --K;
  ll cntTot = fact[tot];
  for (int i = 0; i < 10; ++i) {
    cntTot = mult(cntTot, invFact[dig[i]]);
//    eprintf("cntTot /= fact[%d]\n", dig[i]);
  }
  //eprintf("cntTot %lld\n", cntTot);
  while (tot) {
    for (int i = 0; i <= 10; ++i) {
      assert(i < 10);
      if (!dig[i]) { continue; }
      ll newCntTot;
      if (cntTot > ll(1e13)) {
        int d = gcd(dig[i], tot);
        newCntTot = cntTot / (tot / d) * (dig[i] / d);
      } else {
        newCntTot = cntTot * dig[i] / tot;
      }
//      ll newCntTot = cntTot * dig[i] / tot;
//      assert(cntTot * dig[i] % tot == 0);
//      assert(newCntTot == cntTot * dig[i] / tot);
//      eprintf("newCntTot %lld = %lld * %d / %d (gcd %d)\n", newCntTot, cntTot, dig[i], tot, d);
      if (K >= newCntTot) {
        K -= newCntTot;
      } else {
        cntTot = newCntTot;
        --dig[i];
        --tot;
        ans = (ans * 10 + i) % MOD;
        break;
      }
    }
  }
  printf("%d\n", (int)ans);
}

bool is_prime(ll x) {
  for (ll i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

//  while (!is_prime(P)) {
//    ++P;
//  }
  //printf("P = %lld\n", P);

  logI[0] = 0;
  logFact[0] = 0;
  fact[0] = 1;
  invFact[0] = 1;
  for (int i = 1; i < MAX; ++i) {
    logI[i] = log(i + 0.0);
    logFact[i] = logFact[i - 1] + logI[i];

    inv[i] = inverse(i);
    fact[i] = mult(fact[i - 1], i);
    invFact[i] = mult(invFact[i - 1], inv[i]);
  }
//  return 0;

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    //eprintf("Case %d\n", i);
    solve();
  }

  return 0;
}
