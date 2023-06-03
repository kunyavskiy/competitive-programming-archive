#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("Ofast,no-stack-protector")

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 1001000;
#ifdef TEST
const int BLOCK = 1000;
#else
const int BLOCK = 2000;
#endif
int sorted = 0;
int last = 0;

pair<unsigned, unsigned> increments_[MAXN];
pair<unsigned, unsigned> increments2_[MAXN];
pair<unsigned, unsigned> *increments = increments_;
pair<unsigned, unsigned> *increments2 = increments2_;
unsigned pos[MAXN];
unsigned sum[MAXN];
unsigned val[MAXN];
int sz;
int m;

unsigned get(unsigned r) {
  int rpos = upper_bound(pos, pos + sz, r) - pos - 1;
  unsigned ans = sum[rpos] + val[rpos] * (r - pos[rpos]);
  for (int i = sorted; i < last; i++) {
    if (increments[i].first < r) {
      ans += (r - increments[i].first) * increments[i].second;
    }
  }
  return ans;
}

void rebuild() {
  sort(increments + sorted, increments + last);
  merge(
      increments, increments + sorted,
      increments + sorted, increments + last,
      increments2
  );
  swap(increments, increments2);
  sorted = last;
  pos[0] = sum[0] = val[0] = 0;
  sz = 1;
  for (int i = 0; i <= sorted; i++) {
    if (i == sorted || increments[i].first == pos[sz - 1]) {
      val[sz - 1] += increments[i].second;
    } else {
      pos[sz] = increments[i].first;
      val[sz] = val[sz - 1] + increments[i].second;
      sz++;
    }
  }
  pos[sz] = (1 << m);
  sz++;
  for (int i = 0; i < sz; i++) {
    sum[i + 1] = sum[i] + val[i] * (pos[i + 1] - pos[i]);
  }

#ifdef TEST
  eprintf("======\n");
  for (int i = 0; i < sorted; i++) {
    eprintf("From %u increment %u\n", increments[i].first, increments[i].second);
  }
  for (int i = 0; i < sz; i++) {
    eprintf("pos = %d, val = %d, sum = %d\n", pos[i], val[i], sum[i]);
  }
#endif
}


/** Read */

static const int buf_size = 4096;

static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
  if (buf_pos == buf_len) {
    buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
    if (buf_pos == buf_len)
      return 1;
  }
  return 0;
}

inline int getChar() {
  return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
  return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
  int c;
  while ((c = peekChar()) != -1 && c <= 32)
    buf_pos++;
  return c == -1;
}

inline void skipBlanks() {
  while (!isEof() && buf[buf_pos] <= 32U)
    buf_pos++;
}

inline int readChar() {
  int c = getChar();
  while (c != -1 && c <= 32)
    c = getChar();
  return c;
}

inline int readUInt() {
  int c = readChar(), x = 0;
  while ('0' <= c && c <= '9')
    x = x * 10 + (c - '0'), c = getChar();
  return x;
}

template<class T>
inline T readInt() {
  int minus = 0, c = readChar();
  T x = 0;
  if (c == '-')
    minus = 1, c = getChar();
  else if (c == '+')
    c = getChar();
  for (; '0' <= c && c <= '9'; c = getChar())
    if (minus)
      x = x * 10 - (c - '0'); // take care about -2^{31}
    else
      x = x * 10 + (c - '0');
  return x;
}

inline double readDouble() {
  int s = 1, c = readChar();
  double x = 0;
  if (c == '-')
    s = -1, c = getChar();
  while ('0' <= c && c <= '9')
    x = x * 10 + (c - '0'), c = getChar();
  if (c == '.') {
    c = getChar();
    double coef = 1;
    while ('0' <= c && c <= '9')
      x += (c - '0') * (coef *= 1e-1), c = getChar();
  }
  return s == 1 ? x : -x;
}

inline void readWord(char *s) {
  int c = readChar();
  while (c > 32)
    *s++ = c, c = getChar();
  *s = 0;
}

inline bool readLine(char *s) {
  int c = getChar();
  while (c != '\n' && c != -1)
    *s++ = c, c = getChar();
  *s = 0;
  return c != -1;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  clock_t tot_reb = 0;
  while (scanf("%d%d", &n, &m) == 2) {
    sorted = last = 0;
    unsigned x = 0;

    unsigned mask = (1 << m) - 1;

    for (int i = 1; i <= n; i++) {
      unsigned l = readUInt();
      unsigned r = readUInt();
      l += x;
      r += x;
      l &= mask;
      r &= mask;
      if (l > r) {
        swap(l, r);
      }
      r++;
      increments[last++] = {l, i};
      increments[last++] = {r, -i};

      x += get(r);
      x -= get(l);
      if (i % BLOCK == 0) {
#ifdef LOCAL
        tot_reb -= clock();
#endif
        rebuild();
#ifdef LOCAL
        tot_reb += clock();
#endif
      }
#ifdef TEST
      eprintf("x = %d\n", x);
#endif
    }
    printf("%u\n", x & ((1 << 30) - 1));
  }
  eprintf("total_reb = %lf\n", (tot_reb * 1000.0) / CLOCKS_PER_SEC);


  return 0;
}
