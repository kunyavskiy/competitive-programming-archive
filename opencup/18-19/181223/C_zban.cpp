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
#define mp make_pair
typedef pair<ll, ll> pll;

const int MAXN = 1e7;
int mind[MAXN];
vector<int> primes;

void gen_primes(int n) {
  mind[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (mind[i] == 0) {
      mind[i] = i;
      primes.push_back(i);

    }
    for (int j : primes) {
      if (j > mind[i] || i * j > n) break;
      mind[i * j] = j;
    }
  }
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

// BEGIN ALGO
//return pair(nmod,nr)
//nr%mod1=r1, nr%mod2=r2
//nmod=mod1*mod2/gcd(mod1,mod2)
//if input incosistent return mp(-1,-1)

pll kto (ll mod1, ll r1, ll mod2, ll r2)
{
  ll d=__gcd(mod1,mod2);
  if (r1%d!=r2%d)
    return mp(-1,-1);
  ll rd=r1%d;
  mod1/=d, mod2/=d, r1/=d, r2/=d;

  if (mod1<mod2)
    swap(mod1,mod2), swap(r1,r2);

  ll k=(r2-r1)%mod2;
  if (k<0)
    k+=mod2;

  ll x, y;
  gcdex(mod1,mod2,x,y);
  x%=mod2;
  if (x<0)
    x+=mod2;
  k*=x, k%=mod2;
  return mp(mod1*mod2*d,(k*mod1+r1)*d+rd);
}

bool isPrime(int x) {
  for (int i = 2; 1LL * i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}

vector<int> pr;

const int N = 5e6;
int pmob[N];

int mob(int x) {
  for (int i = 0; i < (int)pr.size() && pr[i] <= x && x >= N; i++) {
    if (x % pr[i] == 0) {
      x /= pr[i];
      if (x %  pr[i] == 0) return 0;
    }
  }
  if (x < N) {
    return pmob[x];
  }
  return 1;
  //return res;
}

double start = clock() / (double)CLOCKS_PER_SEC;


int solve(string s) {
  vector<int> a = {4, 9, 25, 49, 121};
  vector<int> rem(a.size());

  int tt = 0;
  bool TL = 0;
  bool found = 0;
  int answer = -1;
  int checks = 0;

  function<void(int, ll, ll)> rec = [&](int cur, ll cmod, ll crem) {
    if (tt++ % 100 == 0) {
      if (clock() / (double) CLOCKS_PER_SEC - start > 0.8) {
        TL = 1;
      }
    }
    if (TL) return;
    if (found) return;
    if (cur == (int) a.size()) {
      checks++;
      if (crem == 0) return;
      if (crem + (int) s.length() - 1 > (int) 1e9) return;

      int shift = crem;
      while (shift + (int)s.length() - 1 <= (int)1e9) {
        /*if (tt++ % 100 == 0) {
          if (clock() / (double) CLOCKS_PER_SEC - start > 0.8) {
            TL = 1;
          }
        }
        if (TL) return;*/

        bool ok = 1;
        for (int i = 0; i < (int) s.length(); i++) {
          if (abs(mob(shift + i)) != (s[i] - '0')) {
            ok = 0;
            break;
          }
        }
        if (ok) {
          found = 1;
          answer = shift;
        }
        shift += cmod;
      }
      return;
    }
    vector<int> vv;
    for (int rem0 = 0; rem0 < a[cur]; rem0++) {
      bool ok = 1;
      for (int j = (a[cur] - rem0) % a[cur]; j < (int) s.length(); j += a[cur]) {
        if (s[j] == '1') {
          ok = 0;
          break;
        }
      }
      if (!ok) continue;
      vv.push_back(rem0);
    }
    db2(a[cur], vv.size());
    for (int rem0 : vv) {
      rem[cur] = rem0;
      auto o = kto(cmod, crem, a[cur], rem[cur]);
      rec(cur + 1, o.first, o.second);
    }
  };
  rec(0, 1, 0);
  db(checks);
  return answer;
}

void test() {
  string s = "";
  int st = 1e9 - 1e5;
  for (int i = 0; i < 200; i++ ){
    s += (char)('0' + abs(mob(st + i)));
  }
  //for (int i = 0; i < 3; i++) s[177+i]='1';
  cout << solve(s) << endl;
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  //freopen("c.out", "w", stdout);
#endif
  for (int i = 2; 1LL * i * i <= 1.01e9; i++) {
    if (isPrime(i)) {
      pr.push_back(i);
    }
  }

  //cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  gen_primes(N);
  //cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  pmob[0] = 0;
  pmob[1] = 1;
  for (int x = 2; x < N; x++) {
    if (x % (1LL * mind[x] * mind[x]) == 0) {
      pmob[x] = 0;
    } else {
      pmob[x] = pmob[x / mind[x]];
    }
  }
  //cerr << clock() / (double)CLOCKS_PER_SEC << endl;

#ifdef LOCAL
  test();
#endif

  string s;
  while (cin >> s) {
    string tmp;
    for (int i = 0; i < 9; i++) {
      cin >> tmp;
      s += tmp;
    }

    cout << solve(s) << endl;
  }

  return 0;
}
