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

const int MAXN = 3'000'100;

int mind[MAXN];
vector<int> primes;

void gen_primes(int n) {
  mind[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (mind[i] == 0) {
      mind[i] = i;
      primes.push_back(i);
    }
    for (int j: primes) {
      if (j > mind[i] || i * 1LL * j > n) break;
      mind[i * j] = j;
    }
  }
}


std::unordered_map<long long, long long> dp1;
int dp2[2035003][206];
//std::unordered_map<long long, long long> dp2;
long long lim;
int max_prime = 0;
long long max_n = 0;

int calc2(long long n, int k) {
  if (primes[k] > n) return 1;
  if (dp2[n][k] != 0) return dp2[n][k];
  max_n = max(max_n, n);
  max_prime = max(max_prime, k);
  assert(k < (int)primes.size());
  if (k == 0) return n;
  //long long code = (((ll)n) << 40) | k;
  auto &d = dp2[n][k];
  d += calc2(n, k - 1);
  d -= calc2(n / primes[k - 1], k - 1);
  return d;
}


long long calc1(long long n, long long s, int k) {
  assert(k < (int)primes.size());
  if (n * 1LL * primes[k] * primes[k] > lim) {
    long long upto = min(lim / n, s + 1);
    assert(upto < MAXN);
    return max<int>(0, upper_bound(primes.begin(), primes.end(), upto) - (primes.begin() + k)) + 1;
  }
  if (n >= MAXN || n * s >= lim) return calc2(lim / n, k);
  assert(k <= 1800);
  if (primes[k] > s + 1) return 1;
  long long code = (((ll)n) << 40) | k;
  if (dp1.find(code) != dp1.end()) return dp1[code];
  auto &d = dp1[code];
  if (d != 0) return d;
  d = 1;
  while (primes[k] <= s + 1 && n * primes[k] <= lim) {
    ll p = primes[k];
    ll pw = p;
    ll nn = n;
    while (p <= lim / nn) {
      nn *= p;
      pw *= p;
      d += calc1(nn, s * (pw - 1) / (p - 1), k + 1);
    }
    k++;
    if (n * 1LL * primes[k] * primes[k] > lim) {
      long long upto = min(lim / n, s + 1);
      assert(upto < MAXN);
      d += max<int>(0, upper_bound(primes.begin(), primes.end(), upto) - (primes.begin() + k));
      break ;
    }
  }
  return d;
}


int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  gen_primes(MAXN - 1);
  while (scanf("%lld", &lim) == 1) {
    dp1.clear();
    //dp2.clear();
    printf("%lld\n", calc1(1, 1, 0));
    TIMESTAMPf("%12lld %d %d, max = %d, max_n = %lld", lim, (int)dp1.size(), (int)1, max_prime, max_n);
  }

  return 0;
}
