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

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt( T x );
inline void writeChar( int x );
inline void flush();


bool used[1 << 20];

void add(int x) {
  if (used[x]) return;
  used[x] = true;
  int y = x;
  while (y) {
    int bit = y & ~(y - 1);
    add(x ^ bit);
    y ^= bit;
  }
}

int solve(int x) {
  int res = 0;
  for (int i = 19; i >= 0; i--) {
    if (x & (1 << i)) continue;
    if (used[res | (1 << i)]) {
      res |= (1 << i);
    }
  }
  return res * 2 + x;
}

int main() {
#ifdef LOCAL
//  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
#endif

#ifdef TEST
  int n = 1000000;
#else
  int n = readInt();
#endif

  int cur = 0;
  add(cur);

  for (int i = 0; i < n; i++) {
#ifdef TEST
    int x = i;
#else
    int x = readInt();
#endif
    cur ^= x;
    add(cur);
#ifdef TEST
    solve(cur);
#else
    int res = solve(cur);
    writeInt(res);
    writeChar(' ');
#endif
  }
  writeChar('\n');

  flush();

  return 0;
}

/** Read */

static const int buf_size = 4096;

inline int getChar() {
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
}

inline int readChar() {
  int c = getChar();
  while (c <= 32)
    c = getChar();
  return c;
}

template <class T>
inline T readInt() {
  int s = 1, c = readChar();
  T x = 0;
  if (c == '-')
    s = -1, c = getChar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getChar();
  return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
  if (write_pos == buf_size)
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  write_buf[write_pos++] = x;
}

inline void flush() {
  if (write_pos)
    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}

template <class T>
inline void writeInt( T x ) {
  if (x < 0)
    writeChar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    writeChar(s[n]);
}

inline void writeWord( const char *s ) {
  while (*s)
    writeChar(*s++);
}
