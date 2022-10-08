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

const double eps = 1e-7;

typedef long long ll;
typedef long double ld;

inline int getChar();
inline int readChar();
inline int readInt();
inline void writeChar( int x );
inline void flush();
inline void writeInt( int x );
inline void writeDouble(double x);

void writeStr(const char* s) {
  for (int i = 0; s[i]; i++) {
    writeChar(s[i]);
  }
}

void solve() {
  int n = readInt();
  int m = readInt();
  vector<int> minv(n), maxv(n), c(n);
  vector<double> p(n);
  for (int i = 0; i < n; i++) {
    minv[i] = readInt();
    maxv[i] = readInt();
    c[i] = readInt() - 1;
    p[i] = readInt() / 100.0;
  }
  vector<double> v(m);
  double total = 0;
  double any = 0;
  for (int i = 0; i < m; i++) {
    v[i] = readInt();
    total += v[i];
  }

  vector<double> use(n);

  for (int i = 0; i < n; i++) {
    use[i] = minv[i] * p[i];
    v[c[i]] -= use[i];
    any += use[i] / p[i];
    if (v[c[i]] < 0) {
      writeStr("NO\n");
      return;
    }
  }

  if (any > total + eps) {
    writeStr("NO\n");
    return;
  }

  for (int i = 0; i < n; i++) {
    double to_add = (maxv[i] - minv[i]) * p[i];
    to_add = min(to_add, v[c[i]]);
    to_add = min(to_add, (total - any) * p[i]);
    v[c[i]] -= to_add;
    use[i] += to_add;
    any += to_add / p[i];
  }

  if (any < total - eps) {
    writeStr("NO\n");
    return;
  }

  writeStr("YES\n");

  int ptr = 0;
  for (int i = 0; i < n; i++) {
    vector<pair<int, double>> t;
    t.push_back(make_pair(c[i], use[i]));
    double print = use[i] / p[i] - use[i];
    while (ptr < m) {
      if (print < v[ptr]) {
        v[ptr] -= print;
        if (ptr == c[i]) {
          t[0].second += print;
        } else {
          if (print > eps) {
            t.push_back(make_pair(ptr, print));
          }
        }
        break;
      } else {
        if (ptr == c[i]) {
          t[0].second += v[ptr];
        } else {
          if (v[ptr] > eps) {
            t.push_back(make_pair(ptr, v[ptr]));
          }
        }
        print -= v[ptr];
        v[ptr] = 0;
        ptr++;
      }
    }
    writeInt(t.size());
    for (auto x : t) {
      writeChar(' ');
      writeInt(x.first + 1);
      writeChar(' ');
      writeDouble(x.second);
    }
    writeChar('\n');
  }
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif
  int t;
  t = readInt();
  while (t-->0) {
    solve();
  }
  flush();

  return 0;
}

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

inline int readInt() {
  int s = 1, c = readChar();
  int x = 0;
  if (c == '-')
    s = -1, c = getChar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getChar();
  return s == 1 ? x : -x;
}

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

inline void writeInt( int x ) {
  if (x < 0)
    writeChar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    writeChar(s[n]);
}


inline void writeDouble(double x) {
  int part = (int)x;
  x -= part;
  writeInt(part);
  writeChar('.');
  for (int i = 0; i < 8; i++) {
    x *= 10;
    int part = (int)x;
    if (part < 0) part = 0;
    if (part >= 10) part = 9;
    writeChar(part + '0');
    x -= part;
  }
}