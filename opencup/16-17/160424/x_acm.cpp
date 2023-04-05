#define _GLIBCXX_DEBUG
#define __USE_MINGW_ANSI_STDIO 1
#include <bits/stdc++.h>

#include <ctime>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <map>
#include <set>
#include <fstream>
#include <queue>
#include <bitset>

using namespace std;

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

#define TIME 1. * clock() / CLOCKS_PER_SEC

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define forab(i, a, b) for (int i = (a); i <= (b); i++)
#define forabd(i, a, b) for (int i = (b); i >= (a); i--)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define zero(a) memset(a, 0, sizeof(a))
#define copy(a, b) memcpy(a, b, sizeof(b))
#define fill(a, x) memset(a, x, sizeof(a))
#define afill(f, type, value) forn(i, sizeof(f) / sizeof(type)) ((type *)f)[i] = value;
#define pb push_back
#define mp make_pair
#define uni(a) (unique(all(a)) - (a).begin())
#define BS(a, x, less) (lower_bound(all(a), x, less) - (a).begin())
#define CMP(c) []( int i, int j ) { return c[i] < c[j]; } 
#define CMP_GT(c) []( int i, int j ) { return c[i] > c[j]; } 

#define DECLARE(TYPE, NAME, L, R) TYPE _##NAME[(R) - (L) + 1], *NAME = _##NAME - (L)
#define EOL(i, n) " \n"[i == (n) - 1]
#define LEN(a) (int)(sizeof(a) / sizeof(a[0]))
#define IS(a, i) (((a) >> (i)) & 1)
#define ONE(n) ((1 << (n)) - 1)
#define LAST(a) (a)[sz(a) - 1]
#define LASTC(s) (s)[strlen((s)) - 1]
#define BN(x) __builtin_popcountll(x)
#define SWAP(type, a, b) { type tmp = a; a = b; b = tmp; }

typedef short int16;
typedef unsigned short uint16;
typedef unsigned int uint;
typedef double dbl;
typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <string> vs;
typedef pair <int, int> pii;
typedef vector <pii> vpii;
typedef unsigned char byte;

template <class T> T inline sqr(T x) { return x * x; }
template <class T> inline void uix( T &a, T b ) { a = min(a, b); }
template <class T> inline void uax( T &a, T b ) { a = max(a, b); }
void relax( int &a, int b ) { a = min(a, b); }
template <class T> inline T sign( T x ) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }
template <class T> inline T myAbs( T a ) { return a > 0 ? a : -a; }
template <class T> T iteratorK( T a, int k ) { while (k--) a++; return a; }
template <class T> string str( T i ) { stringstream ss; ss << i; return ss.str(); }

#define DEBUG

#ifdef DEBUG
#  define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#  define debug(x) cerr << #x = ""
#else
#  define err(...) 
#  define debug(x) 
#endif

void Assert( bool f, const char *fmt = "", ... ) {
  if (!f) {
    va_list list;
    va_start(list, fmt);
    err(fmt, list);
    exit(1);
  }
}

inline unsigned R() { return (rand() << 15) ^ rand(); }

double start = clock();
void timeX( const char *s = 0, ... ) {
  va_list list;
  va_start(list, s);
  if (s) {
    fprintf(stderr, "time = %.2f : ", (clock() - start) / CLOCKS_PER_SEC);
    vfprintf(stderr, s, list);
    fprintf(stderr, "\n");
  }
  else
    fprintf(stderr, "time = %.2f\n", (clock() - start) / CLOCKS_PER_SEC);
  start = clock();
}

void timeS( const char *s = 0 ) { fprintf(stderr, "time = %.2f : %s\n", 1. * clock() / CLOCKS_PER_SEC, s ? s : ""); }

const int MOD = 1e9 + 7;
inline void add( int &a, int b ) { if ((a += b) >= MOD) a -= MOD; }
inline void sub( int &a, int b ) { if ((a -= b) < 0) a += MOD; }
inline int mul( int a, int b ) { return (ll)a * b % MOD; }

int main() {
#if DEBUG
  double tmp_start = clock();
  err("Start\n");
#endif

  #define NAME "computer"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  ios_base::sync_with_stdio(0), cin.tie(0);

#if DEBUG
  err("Total time = %.2f\n", (clock() - tmp_start) / CLOCKS_PER_SEC);
#endif
  
  fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
  return 0;
}
// public static void main( String[] args ) {

inline bool randBit() {
	static unsigned bn = 0, x;
	if (!bn)
		bn = 15, x = rand();
	bool res = x & 1;
	bn--, x >>= 1;
	return res;
}
