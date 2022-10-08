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

typedef vector<int> vi;

#define sz(v) ((int)((v).size()))

const int MOD = 998244353;
const int ROOT = 3;

int mmul(int a, int b) {
  return (a * 1LL * b) % MOD;
}
void madd(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

int mpow(int a, int b){
  if (!b) return 1;
  if (b & 1) return (mpow(a, b-1) * 1LL * a) % MOD;
  int temp = mpow(a, b/2);
  return (temp * 1LL * temp) % MOD;
}

bool checkRoot(int x){
  return mpow(x, (MOD - 1) / 7) != 1 && mpow(x, (MOD - 1) / 17) != 1 && mpow(x, (MOD - 1) / 2) != 1;
}

// BEGIN ALGO
const int MROOT = 19;
const int MROOTP = 1<<MROOT;
int rts[MROOTP + 10], brev[MROOTP + 10];
// \emph{Don't forget to call before}
void PreCalcRoots(){
  rts[0] = 1; // ROOT is primary root for MOD
  rts[1] = mpow(ROOT, (MOD-1) / MROOTP);
  for (int i = 2; i < MROOTP; i++)
    rts[i] = mmul(rts[i-1], rts[1]);
  for (int i = 0; i < MROOTP; i++) /*BOXNEXT*/
    brev[i] = (brev[i>>1]>>1) | ((i&1) << (MROOT-1));
}
inline void butterfly(int &a, int &b, int x){
  int temp = mmul(x, b); b = a;
  madd(a, temp); madd(b, MOD - temp);
}
void fft(vi &a, bool inv){
  int n = __builtin_ctz(sz(a));
  for (int i = 0; i < (1<<n); i++){
    int temp = brev[i] >> (MROOT - n);
    if (temp > i) swap(a[i], a[temp]);
  }
  for (int step = 0; step < n; step++){
    int pos = 0; /*BOXNEXT*/
    int dlt = (inv ? -1 : 1) * (1 << (MROOT - step - 1));
    for (int i = 0; i < (1<<n); i++){
      if ((i ^ (1<<step)) > i) /*BOXNEXT*/
        butterfly(a[i], a[i ^ (1<<step)], rts[pos]);
      pos = (pos + dlt) & (MROOTP-1);
    }
  }
}
vi multiply(vi a, vi b){
  int rsz = sz(a) + sz(b), rsz2 = 1;
  while (rsz2 < rsz) rsz2 *= 2;
  a.resize(rsz2); b.resize(rsz2);
  fft(a, false); fft(b, false);
  for (int i = 0; i < sz(a); i++)
    a[i] = mmul(a[i], b[i]);
  fft(a, true);
  int in = mpow(sz(a), MOD - 2);
  for (int i = 0; i < sz(a); i++)
    a[i] = mmul(a[i], in);
  return a;
}
vi inverse(vi a){
  assert(a[0] != 0);
  vi x(1, mpow(a[0], MOD - 2));
  while (sz(x) < sz(a)) { /*BOXNEXT*/
    vi temp(a.begin(), a.begin() + min(sz(a), 2*sz(x)));
    vi nx = multiply(multiply(x, x), temp);
    x.resize(2*sz(x));
    for (int i = 0; i < sz(x); i++) /*BOXNEXT*/
      madd(x[i], x[i]), madd(x[i], MOD - nx[i]);
  }
  return x;
}
// END ALGO

const int MAXN = 257000;

int facs[MAXN];
int ifacs[MAXN];

void PreCalcFacs(){
  facs[0] = ifacs[0] = 1;
  for (int i = 1; i < MAXN; i++){
    facs[i] = (facs[i-1] * 1LL * i) % MOD;
    ifacs[i] = mpow(facs[i], MOD - 2);
  }
}

int cnk(int n, int k){
  if (n < 0 || k < 0 || k > n) return false;
  int res = facs[n];
  res = (res * 1LL * ifacs[k]) % MOD;
  res = (res * 1LL * ifacs[n-k]) % MOD;
  return res;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  PreCalcFacs();
      PreCalcRoots();
  int n, m;
  scanf("%d%d", &n, &m);
  assert(n == m);

  vi c(n + 1);
  for (int i = 0; i <= n; i++) {
    c[i] = mmul(cnk(2 * i, i), mpow(i + 1, MOD - 2));
  }

  vi c1(n + 1);
  c1[0] = 1;
  for (int i = 1; i <= n; i++) {
    c1[i] = MOD - c[i - 1];
    c1[i] = mmul(c1[i], 2);
  }
  vi c2(n + 1);
  c2[0] = 0;
  for (int i = 1; i <= n; i++) {
    c2[i] = c2[i - 1] + c[i - 1] * (i + mpow(2, MOD - 2));
  }

  vi res = multiply(c2, inverse(c1));

  int ans = res[n];
  ans = mmul(ans, cnk(n + n, m));

  printf("%d\n", res[n]);

  return 0;
}
