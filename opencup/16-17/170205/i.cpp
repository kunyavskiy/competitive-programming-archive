#include <bits/stdc++.h>
using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;
typedef pair<ll, ll> pll;

const int EPS = 10;
const int N = 2 * 250000 + EPS;

char s[N], s0[N];
int b[N], f[N], ans[N];

ll pref0[N];
ll pref1[N];

void cor( int *a ) {
	forn(i, N)
		if (a[i] >= 10)
			a[i + 1] += a[i] / 10, a[i] %= 10;
}

void out( int *a ) {
  cor(a);
	int len = N - 1;
	while (len && !a[len])
		len--;
	while (len >= 0)
		printf("%d", a[len--]);
  printf("\n");
}

bool incrementBigInt(int n, char *s) {
  int i = n - 1;
  while (i >= 0 && s[i] == '9') {
    --i;
  }
  if (i < 0) { return false; }

  i = n - 1;
  while (i >= 0 && s[i] == '9') {
    s[i] = '0';
    --i;
  }
  assert(i >= 0 && s[i] < '9');
  s[i]++;
  return true;
}

// struct RangeTree {
//   int kk;
//   vector <pll> val;
//   vector <pll> add;

//   RangeTree(int n) {
//     kk = 1;
//     while (kk < n) {
//       kk *= 2;
//     }
//     val.assign(2 * kk + 10, pll(0, 0));
//     add.assign(2 * kk + 10, pll(0, 0));
//   }

//   void doAdd(int t, int L, int R, pll delta) {
//     doAdd(1, 0, kk - 1, L, R);
//   }

//   void doAdd(int t, int Lt, int Rt, int L, int R, pll delta) {
//     if (Rt < L || R < Lt) { return; }
//     if (L <= Lt && Rt <= R) {
//       addEntire(t, Lt, Rt, delta);
//       return;
//     }
//     int Mt = (Lt + Rt) / 2;
//     pushModify(t, Lt, Rt);
//     doAdd(2 * t, Lt, Mt, L, R, delta);
//     doAdd(2 * t + 1, Mt + 1, Rt, L, R, delta);
//     update(t);
//   }

//   void update(int t) {
//     val[t] = val[2 * t] + val[2 * t + 1];
//   }

//   void pushModify(int t, int Lt, int Rt) {
//     int Mt = (Lt + Rt) / 2;
//     addEntire(2 * t, Lt, Mt, add[t]);
//     addEntire(2 * t + 1, Mt + 1, Rt, add[t]);
//     add[t] = pll(0, 0);
//   }
// };

void add(int L, int R, ll x, ll y) {
  pref0[L] += x;
  pref0[R] -= x;
  pref1[L] += y;
  pref1[R] -= y;
}


const int maxlog = 20, maxn = 1 << maxlog;

typedef double dbl;

struct num {
  dbl x, y;
  num() { }
  num( dbl a ) : x(cos(a)), y(sin(a)) { }
  num( dbl x, dbl y ) : x(x), y(y) { }
  num operator * ( double k ) const     { return num(x * k, y * k); }
  num operator + ( const num &a ) const { return num(x + a.x, y + a.y); }
  num operator - ( const num &a ) const { return num(x - a.x, y - a.y); }
  num operator * ( const num &a ) const { return num(x * a.x - y * a.y, x * a.y + y * a.x); }
  num ort() { return num(x, -y); }
};
num root[maxn];
int rev[maxn];

void fft( const num *a, num *res ) {
  forn(i, maxn)
    res[rev[i]] = a[i];
  for (int k = 1; k < maxn; k *= 2)
    for (int i = 0; i < maxn; i += 2 * k)
      forn(j, k) {
        num tmp = root[k + j] * res[i + j + k];
        res[i + j + k] = res[i + j] - tmp;
        res[i + j] = res[i + j] + tmp;
      }
}

void precalc() {
  forn(i, maxn)
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (maxlog - 1));
  for (int k = 1; k < maxn; k *= 2) {
    num tmp(M_PI / k);
    root[k] = {1, 0};
    for (int i = 1; i < k; i++)
      root[k + i] = (i & 1) ? root[(k + i) >> 1] * tmp : root[(k + i) >> 1]; // Way #2
  }
}

num A[maxn], B[maxn];
num FA[maxn], FB[maxn];

void get_product( int *a, int *b, int *c ) {
  forn(i, maxn) {
    A[i] = num(a[i], 0);
    B[i] = num(b[N - i - 1], 0);
  }
  fft(A, FA);
  fft(B, FB);
  forn(i, maxn) FA[i] = FA[i] * FB[i];
  fft(FA, A);
  reverse(a + 1, a + maxn);
  forn(i, maxn) {
    int j = i - (N - 1);
    if (j >= 0) c[j] = (int)(A[i].x / maxn + 0.5);
  }
}

int s_sum[N];

int main() {
  precalc();
	scanf("%s", s);
	int n = strlen(s);
  strcpy(s0, s);
  forn(i, n)
    s_sum[i + 1] = s_sum[i] + (9 - (s[i] - '0'));
  if (incrementBigInt(n, s)) {
    #define minD ((k == 0 ? 1 : 0))
    #define maxD (s[k] - '0' - 1)
    #define cntD (maxD - minD + 1)
    for (int k = 0; k < n; ++k) {
      for (int j = 0; j < n - k - 1; ++j) {
        ans[j + n - k - 1] += s_sum[k] * cntD;
      }
      for (int j = n - k - 1; j < n ; ++j) {
        ans[j + n - k - 1] += s_sum[n - j - 1] * cntD; 
      }
    }
    for (int k = 0; k < n; ++k) {
      int x = 9 * cntD - cntD * (maxD + minD) / 2;
      add(n - k - 1, 2 * (n - k - 1), x, 0);
      // pref0[n - k - 1] += x;
      // pref0[2 * (n - k - 1)] -= x;
      // for (int j = 0; j < n - 1 - k; ++j) {
      //   ans[j + n - k - 1] += 9 * cntD - cntD * (maxD + minD) / 2;
      // }
    }
    for (int k = 0; k < n; ++k) {
      int x0 = 2 * (n - k - 2) * 45 * cntD;
      int x1 = -45 * cntD;
      add(n - k - 2, n - k - 2 + (n - k - 1), x0, x1);
      // for (int j = 0; j < n - k - 1; ++j) {
      //   ans[j + n - k - 2] += 45 * cntD * (n - k - 2 - j);
      // }
    }
    for (int i = 0; i < 2 * n; ++i) {
      if (i) {
        pref0[i] += pref0[i - 1];
        pref1[i] += pref1[i - 1];
      }
      ans[i] += pref0[i];
      ans[i] += pref1[i] * i;
    }
    n--;
  }
  strcpy(s, s0);

  { // calc B
    int x = n - 1;
    for (int i = 0; i <= x; i++)
      b[x - i] = b[x + i] = (n - i) / 2;
  }

  { // calc F
    int sum = 0, x = n - 2, add = 0;
    for (int i = 0; i <= x; i++) {
      f[i] = sum;
      if (i % 2 == 0) add++;
      sum += add;
    }
    for (int i = 0; i <= x; i++)
      f[x + i] = f[x - i];
  }

  forn(i, N)
    ans[i] += b[i] * 36;
  forn(i, N)
    ans[i] += f[i] * 9 * 45;

	out(ans); 
}

