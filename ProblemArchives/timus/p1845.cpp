#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <complex>
#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME "1845"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector<pii> vpii;

const int inf = 1e9;
const double eps = 1e-9;
const int INF = inf;
const double EPS = eps;

#ifdef LOCAL
struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __Timestamper;
#else
struct __timestamper {};
#endif

/*Template end*/

typedef complex<ll> T;

ll mdel (ll v, ld d)
{ 
  if (v<0)
    return -mdel(-v,d);
  return (ll)(v/d+0.5);
}

ll mabs (T a)
{
  return a.real()*a.real()+a.imag()*a.imag();
}

T operator % (T a, T b)
{
  //cerr<<"in   "<<a<<" "<<b<<endl;
  T tmp=a*conj(b);
  ll x=tmp.real();
  ll y=tmp.imag();
  ll d=mabs(b);
  a-=b*mdel(x,d);
  a-=b*mdel(y,d)*T(0,1);
  //cerr<<x<<" "<<y<<" "<<d<<"  "<<mdel(x,d)<<" "<<mdel(y,d)<<"     "<<a<<endl;
  //T ta=a-b;
  //if (mabs(ta)<)
  assert(mabs(a)<mabs(b));
  //cerr<<"out"<<endl;
  return a;
}

T read() {
  int x, y;
  assert(scanf("%d%d", &x, &y) == 2);
  return T(x,y);
}

void println(const T& v) {
  printf("%d %d\n", (int)v.real(), (int)v.imag());
}

T mod;

T mmod(T x) {
  x = x%mod;
  return x;
}
void madd(T &a, const T &b) {
  a = mmod(a + b);
}
T mmul(T a, T b) {
  return mmod(a * b % mod);
}

const int MAXN = 55;
T d[MAXN + 1][MAXN + 1][MAXN + 1][2];

int main()
{
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<vector<T> > mat(n, vector<T>(n));
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      mat[i][j] = read();
    mod = read();
    
    memset(d, 0, sizeof d);
    d[0][0][0][1] = 1;
    for (int len = 0; len <= n; len++)
    for (int i = 0; i < n; i++) {
      madd(d[len][i][i][1],-d[len][i][i][0]);
      madd(d[len][i + 1][i + 1][1], d[len][i][i][1]);
      if (len < n) {
        for (int j = i; j < n; j++) {
          madd(d[len+1][i][j][0],mmul(d[len][i][i][1],-mat[i][j]));
          for (int k = i; k < n; k++) {
            T tmp = mmul(d[len][i][j][0], -mat[j][k]);
            madd(d[len + 1][i][k][0], tmp);
          }
        }
      }
    }
    /*for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        for (int k=0; k<n; k++)
          for (int t=0; t<2; t++)
            if (d[i][j][k][t])
              eprintf("%d %d %d %d %d\n", i, j, k, t, d[i][j][k][t]);*/
    println(d[n][n][n][1]);
  }

  return 0;
}
