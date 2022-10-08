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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ((_WIN32 || __WIN32__) && __cplusplus < 201103L)
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

inline int getChar();
inline int readChar();
inline int readInt();
inline void writeChar(int x);
inline void flush();
inline void writeInt(int x);
inline void writeDouble(double x);
void writeStr(const char *s);

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int n, m, k;
vector<string> s;

int good(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m;
}

int count(int x, int y) {
  if (!good(x, y) || s[x][y] != '*') {
    return 0;
  }
  int ans = 0;
  for (int i = 0; i < 4; i++) {
    int nx1 = x + dx[i];
    int nx2 = x + dx[(i + 1) % 4];
    int ny1 = y + dy[i];
    int ny2 = y + dy[(i + 1) % 4];
    if (good(nx1, ny1) && good(nx2, ny2) && s[nx1][ny1] == '*' && s[nx2][ny2] == '*') {
      ans++;
    }
  }
  return ans;
}

int count_all(int x, int y) {
  int ans = 0;
  for (int i = 0; i < 4; i++) {
    ans += count(x + dx[i], y + dy[i]);
  }
  ans += count(x, y);
  return ans;
}

int diff(int x, int y) {
  int c = count_all(x, y);
  s[x][y] = '*';
  c = count_all(x, y) - c;
  s[x][y] = '.';
  return c;
}

void doit(int x, int y) {
  int d = diff(x, y);
  if (d <= k) {
    k -= d;
    s[x][y] = '*';
  }
/*
  eprintf("k = %d, d = %d\n", k, d);
  for (int i = 0; i < n; i++) {
    eprintf("%s\n", s[i].c_str());
  }
*/
}

void try1() {
  for (int i = 1; i < n - 1; i++) {
    for (int j = 0; j < m && k; j++) {
      doit(i, j);
    }
  }

  for (int i = 0; i < m - 2 && k; i++) {
    doit(0, i);
    doit(n - 1, i);
  }
  if (k) {
    doit(0, m - 2);
    doit(0, m - 1);
    doit(n - 1, m - 2);
    doit(n - 1, m - 1);
  }
}

void try2() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m && k; j++) {
      doit(i, j);
    }
  }
}

void try3() {
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n && k; i++) {
      doit(i, j);
    }
  }

}

void solve() {
  n = readInt();
  m = readInt();
  k = readInt();
  int k0 = k;
  s = vector<string> (n, string(m, '.'));

  try1();
  if (k) {
    k = k0;
    s = vector<string> (n, string(m, '.'));
    try2();
    if (k) {
      k = k0;
      s = vector<string> (n, string(m, '.'));
      try3();
    }
  }

  #ifdef LOCAL
  if (n * m <= 20 && k) {
    int c = n * m;
    for (int mask = 0; mask < (1 << c); mask++) {
      int ptr = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          s[i][j] = (mask & (1 << ptr)) ? '*' : '.';
          ptr++;
        }
      }
      int ans = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          ans += count(i, j);
        }
      }
      if (ans == k0) {
        eprintf("k0 = %d\n", k0);
        for (int i = 0; i < n; i++) {
          eprintf("%s\n", s[i].c_str());
        }
      }
      assert(ans != k0);
    }
  }
  #endif

  if (!k) {
    for (int i = 0; i < n; i++) {
      writeStr(s[i].c_str());
      writeChar('\n');
    }
  } else {
    writeInt(-1);
    writeChar('\n');
  }
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int t = readInt();
  while (t --> 0) {
    solve();
    if (t) {
      writeChar('\n');
    }
  }

  return 0;
}

static const int buf_size = 4096;

inline int getChar() {
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len) {
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  }
  if (pos == len) {
    return -1;
  }
  return buf[pos++];
}

inline int readChar() {
  int c = getChar();
  while (c <= 32) {
    c = getChar();
  }
  return c;
}

inline int readInt() {
  int s = 1, c = readChar();
  int x = 0;
  if (c == '-') {
    s = -1, c = getChar();
  }
  while ('0' <= c && c <= '9') {
    x = x * 10 + c - '0', c = getChar();
  }
  return s == 1 ? x : -x;
}

void writeStr(const char *s) {
  for (int i = 0; s[i]; i++) {
    writeChar(s[i]);
  }
}

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x) {
  if (write_pos == buf_size) {
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  }
  write_buf[write_pos++] = x;
}

inline void flush() {
  if (write_pos) {
    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
  }
}

class Flusher {
  public:
    ~Flusher() {
      flush();
    }
} my_flusher;

inline void writeInt(int x) {
  if (x < 0) {
    writeChar('-'), x = -x;
  }

  char s[24];
  int n = 0;
  while (x || !n) {
    s[n++] = '0' + x % 10, x /= 10;
  }
  while (n--) {
    writeChar(s[n]);
  }
}

inline void writeDouble(double x) {
  int part = (int)x;
  x -= part;
  writeInt(part);
  writeChar('.');
  for (int i = 0; i < 8; i++) {
    x *= 10;
    int part = (int)x;
    if (part < 0) {
      part = 0;
    }
    if (part >= 10) {
      part = 9;
    }
    writeChar(part + '0');
    x -= part;
  }
}
