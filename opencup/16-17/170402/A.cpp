//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "A"

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

vector<ll> ans;

vector<int> primes;

ll n;

bool isPrime(int a) {
  for (int i = 2; i < a; i++)
    if (a % i == 0)
      return false;
  return true;
}

bool check(ll val, ll limit, ll min) {
  while (limit > 0) {
    if (n / min < val) {
      return false;
    }
    val *= min;
    limit--;
  }
  return val <= n;
}

void go(ll val, ll num, ll den, int pos) {
//  eprintf("%lld %lld\n",  num, den);
  if (num < 0) return;
  ll g = __gcd(num, den);
  num /= g;
  den /= g;
  if (den > 1) return;
  if (num == 0 && den == 1) {
    ans.push_back(val);
  }
  if (pos == (int)primes.size()) return;
  int p = primes[pos];
  if (!check(val, (num * p + den - 1) / den, p)) return;
  go(val, num, den, pos + 1);
  int k = 0;
  while (val <= n / p) {
    val *= p;
    k++;
    go(val, num * p - den * k, den * p, pos + 1);
  }
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

  for (int i = 2; i < 100; i++)
    if (isPrime(i)) {
      primes.push_back(i);
    }

  int k;
  scanf("%d%lld", &k, &n);
  go(1, k, 1, 0);
  sort(ans.begin(), ans.end());
  ans.erase(unique(ans.begin(), ans.end()), ans.end());
  printf("%d\n", (int)ans.size());
  for (int i = 0; i < (int)ans.size(); i++) {
    printf("%lld ", ans[i]);
  }
  printf("\n");
  return 0;
}
