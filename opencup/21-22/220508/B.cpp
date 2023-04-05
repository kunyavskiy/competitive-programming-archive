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

typedef long long ll;
typedef long double ld;

const int MAXN = 1.1e9;
vector<bool> is_prime;
vector<int> primes;

void gen_primes(int n) {
  is_prime.resize(n + 1, true);
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      for (ll j = 2LL * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

bool check(ll x, int y) {
  if (x % 2 != 0) return false;
  while (x % 2 == 0) x /= 2;
  return x == y;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif


  long long n;
  scanf("%lld", &n);
  if (n >= 2431) {
    printf("1\n");
  } else {
    printf("0\n");
  }
  return 0;
  eprintf("n = %lld\n", n);
  gen_primes(MAXN - 1);

  ll ans = 0;
  ll ans1 = 0;
  ll ans2 = 0;

  for (int i = 0; i < (int)primes.size(); i++) {
    long long prod = primes[i];
    int j = i + 1;
    while (j < (int)primes.size()) {
      //printf("%d *...[%d] = %lld ?= 2^k * %d - 1\n", primes[i], j - i, prod, primes[j]);
      if (check(prod + 1, primes[j])) {
        printf("%d *...[%d] = %lld = 2^k * %d - 1\n", primes[i], j - i, prod, primes[j]);
        ans++;
        if (j == i + 1) ans1++;
        if (j == i + 2) ans2++;
      }
      if (__int128(prod) * __int128(primes[j]) > n) break;
      prod *= primes[j];
      j++;
    }
  }

  printf("%lld\n", ans);
  eprintf("%lld %lld %lld\n", ans, ans1, ans2);


  return 0;
}
