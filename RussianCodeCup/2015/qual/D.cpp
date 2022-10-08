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

#define TASKNAME "D"

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

void gen_fib(int mod, vector<int>& v) {
  v.pb(1);
  v.pb(1);
  int pos = 1;
  while (pos++) {
    int next = (v[pos-1] + v[pos - 2]) % mod;
    if (v.back() == 1 && next == 1){
      v.pop_back();
      break;
    }
    v.pb(next);
  }
}

const int K = 4;
const int mods[K] = {3, 121, 61, 45161};
const int phi[K] = {2, 110, 60, 45160};
vector<int> fib[K];

int pow(int a, long long b, int mod) {
  int res = 1;
  while (b) {
    if (b & 1) res = (res * a) % mod;
    a = (a * a) % mod; 
    b >>= 1;
  }
  return res;
}

void gcdex(ll a,ll b,ll &x,ll &y) {
  if (!a){
    x = 0, y = 1;
    return;
  }
  ll x1, y1;
  gcdex(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
}

typedef pair<ll,ll> pll;

pll kto (ll mod1, ll r1, ll mod2, ll r2)
{
  if (mod1<mod2)
    swap(mod1,mod2), swap(r1,r2);
  
  ll k=((r2 - r1 + mod2)%mod2 + mod2) % mod2;
  
  ll x, y;
  gcdex(mod1,mod2,x,y);
  x%=mod2;
  if (x<0)
    x+=mod2;
  k*=x, k%=mod2;
  return mp(mod1*mod2,k*mod1+r1);
}


int solve(int n, long long k, const vector<int>& v, int mod, int phimod) {
  (void)phimod;
  int ans = 0;
  if (k > phimod) {
    k = phimod + k % phimod;
  }
  //k %= phimod;
  int sz = (int)v.size();
  for (int i = 0; i < sz; i++){
    ans = (ans + (n / sz + (i < n % sz)) * 1LL * pow(v[i], k, mod)) % mod;
  }
  //eprintf("%d ", ans);
  return ans;
}

void solve() {
  int n; long long k;
  scanf("%d%lld", &n, &k);
  vector<int> vals(K);
  for (int i = 0; i < K; i++) {
    vals[i] = solve(n, k, fib[i], mods[i], phi[i]);
  }
  pll res(1LL, 1LL);
  for (int i = 0; i < K; i++)
    res = kto(res.first, res.second, mods[i], vals[i]);
  assert(res.first == 1000000023);
  printf("%d\n", (int)res.second);
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  for (int i = 0; i < K; i++) {
    gen_fib(mods[i], fib[i]);
  }

  int t;
  scanf("%d",&t);
  while (t-->0)
    solve();
      
  return 0;
}
