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

#define TASKNAME "E"

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

inline int getChar();
inline int readChar();
inline int readInt();
inline void writeChar( int x );
inline void flush();
inline void writeInt( ll x );


vector<int> a;
vector<int> as;
vector<ll> cur;
vector<int> l, r;

vector<ll> bit;



struct event {
  int pos;
  int id;
  int type;
  int upto;
  event() {

  }
  event(int pos, int id, int type, int upto) {
    this->pos = pos;
    this->id = id;
    this->type = type;
    this->upto = upto;
  }
  bool operator<(const event& rhs) const {
    return this->pos < rhs.pos;
  }
};

int convert(ll val) {
  return upper_bound(as.begin(), as.end(), val) - as.begin() - 1;
}

ll bit_get(int r) {
  ll res = 0;
  while (r != -1) {
    res += bit[r];
    r = (r & (r + 1)) - 1;
  }
  return res;
}

void bit_update(int pos, ll val) {
  while (pos < (int)bit.size()) {
    bit[pos] += val;
    pos |= (pos + 1);
  }
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, m;
  n = readInt();
  m = readInt();

  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i] = readInt();
  }
  cur.resize(m);
  l.resize(m);
  r.resize(m);

  for (int i = 0; i < m; i++) {
    l[i] = readInt() - 1;
    r[i] = readInt() - 1;
    cur[i] = 1;
  }


  as = a;
  sort(as.begin(), as.end());
  as.erase(unique(as.begin(), as.end()), as.end());

  vector<int> ac = vector<int>(n);

  for (int i = 0; i < n; i++) {
    ac[i] = convert(a[i]);
  }
  /*

  vector<int> lord(n);
  vector<int> rord(n);

  for (int i = 0; i < n; i++) {
    lord[i] = rord[i] = 0;
  }

  sort(lord.begin(), lord.end(), [](int a, int b) {
  return l[a] < l[b];
  });
  sort(rord.begin(), rord.end(), [](int a, int b) {
  return r[a] < r[b];
  });
*/

  bool any = false;

  for (int it = 0; it < 50; it++) {
    vector<event> v(2*m);
    vector<ll> result(m);
    for (int i = 0; i < m; i++) {
      int temp = convert(cur[i]);
      v[i] = event(l[i] - 1, i, -1, temp);
      v[i + m] = event(r[i], i, 1, temp);
      result[i] = 1;
    }
    bit = vector<ll>(as.size());

    sort(v.begin(), v.end());
    int ptr = 0;
    for (int i = 0; i <= n; i++) {
      while (ptr < (int)v.size() && v[ptr].pos < i) {
        result[v[ptr].id] += v[ptr].type * bit_get(v[ptr].upto);
        ptr++;
      }
      if (i != n) {
        bit_update(ac[i], a[i]);
      }
    }

    for (int i = 0; i < m; i++) {
      if (cur[i] != result[i]) any = true;
      cur[i] = result[i];
    }

    if (!any) break;

  }

  for (int i = 0; i < m; i++) {
    writeInt(cur[i]);
    writeChar('\n');
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

inline void writeInt( ll x ) {
  if (x < 0)
    writeChar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    writeChar(s[n]);
}

