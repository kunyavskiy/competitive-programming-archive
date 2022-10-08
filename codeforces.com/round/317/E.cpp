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

#define TASKNAME "E"

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

vector<int> primes;

void factor(int x){
  for (int i = 2; i * i <= x; i++){
    if (x % i == 0) primes.push_back(i);
    while (x % i == 0) x /= i;
  }
  if (x != 1) primes.push_back(x);
}

vector<long long> factor2(int x) {
  vector<long long> res(primes.size());
  for (int i = 0; i < (int)primes.size(); i++)
    while (x % primes[i] == 0) {
      x /= primes[i];
      res[i]++;
    }
  return res;
}

const int MOD = 1000000007;

long long pow(long long a, long long b) {
  if (b == 1) return a % MOD;
  if (b & 1) return (pow(a, b - 1) * a) % MOD;
  long long temp = pow(a, b/2);
  return (temp * temp ) % MOD;
}

void mult(vector<long long>& a, long long coef){
  if (coef == 1) return;
  for (long long& x : a) x *= coef;
}

void add(vector<long long>& a, const vector<long long>& b, long long coef){
  for (int i = 0; i < (int)a.size(); i++)
    a[i] += b[i] * coef;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int n;
  scanf("%d",&n);
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    scanf("%d%d",&a[i], &b[i]);
  for (int i = 0; i < n; i++) {
    factor(a[i]);
    factor(b[i]);
  }
  sort(primes.begin(), primes.end());
  primes.erase(unique(primes.begin(), primes.end()), primes.end());

  vector<long long> tota = factor2(a[0]);
  vector<long long> totb = factor2(b[0]);

  #define EXIT do { printf("-1\n"); exit(0);} while (0)

  for (int i = 1; i < n; i++) {
    vector<long long> cura = factor2(a[i]);
    vector<long long> curb = factor2(b[i]);
    for (int j = 0; j < (int)primes.size(); j++) {
      long long g = __gcd(curb[i], totb[j]);
      if (g == 0 || (tota[j] - cura[j]) % g) EXIT;
      while (tota[j] != cura[j]) {
        if (tota[j] < cura[j]) {
          if (totb[j] == 0) EXIT;
          add(tota, totb, (cura[j] - tota[j] + totb[j] - 1) / totb[j]);
        } else {
          if (curb[j] == 0) EXIT;
          add(cura, curb, (tota[j] - cura[j] + curb[j] - 1) / curb[j]);
        }
      }
      mult(totb,curb[i] / g);
      mult(curb,totb[i] / g);
    }
  }

  long long ans = 1;
  for (int i = 0; i < (int)primes.size(); i++)
    ans = (ans * 1LL * pow((long long)primes[i], tota[i])) % MOD;

  printf("%lld\n", ans);

      
  return 0;
}
