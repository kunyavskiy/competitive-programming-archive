#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


using namespace std;

namespace Input {

/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define VERSION "0.1.5"

#include <cassert>
#include <cstdio>
#include <algorithm>

/** Fast allocation */

#ifdef FAST_ALLOCATOR_MEMORY
  int allocator_pos = 0;
	char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
	inline void * operator new ( size_t n ) {
		char *res = allocator_memory + allocator_pos;
		allocator_pos += n;
		assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
		return (void *)res;
	}
	inline void operator delete ( void * ) noexcept { }
	//inline void * operator new [] ( size_t ) { assert(0); }
	//inline void operator delete [] ( void * ) { assert(0); }
#endif

/** Fast input-output */

  template <class T = int> inline T readInt();
  inline double readDouble();
  inline int readUInt();
  inline int readChar(); // first non-blank character
  inline void readWord( char *s );
  inline bool readLine( char *s ); // do not save '\n'
  inline bool isEof();
  inline int getChar();
  inline int peekChar();
  inline bool seekEof();
  inline void skipBlanks();

  template <class T> inline void writeInt( T x, char end = 0, int len = -1 );
  inline void writeChar( int x );
  inline void writeWord( const char *s );
  inline void writeDouble( double x, int len = 0 );
  inline void flush();

  static struct buffer_flusher_t {
    ~buffer_flusher_t() {
      flush();
    }
  } buffer_flusher;

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
      x = x * 10 + c - '0', c = getChar();
    return x;
  }

  template <class T>
  inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
      s = -1, c = getChar();
    else if (c == '+')
      c = getChar();
    while ('0' <= c && c <= '9')
      x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
  }

  inline double readDouble() {
    int s = 1, c = readChar();
    double x = 0;
    if (c == '-')
      s = -1, c = getChar();
    while ('0' <= c && c <= '9')
      x = x * 10 + c - '0', c = getChar();
    if (c == '.') {
      c = getChar();
      double coef = 1;
      while ('0' <= c && c <= '9')
        x += (c - '0') * (coef *= 1e-1), c = getChar();
    }
    return s == 1 ? x : -x;
  }

  inline void readWord( char *s ) {
    int c = readChar();
    while (c > 32)
      *s++ = c, c = getChar();
    *s = 0;
  }

  inline bool readLine( char *s ) {
    int c = getChar();
    while (c != '\n' && c != -1)
      *s++ = c, c = getChar();
    *s = 0;
    return c != -1;
  }

/** Write */

  static int write_buf_pos = 0;
  static char write_buf[buf_size];

  inline void writeChar( int x ) {
    if (write_buf_pos == buf_size)
      fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
    write_buf[write_buf_pos++] = x;
  }

  inline void flush() {
    if (write_buf_pos) {
      fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
      fflush(stdout);
    }
  }

  template <class T>
  inline void writeInt( T x, char end, int output_len ) {
    if (x < 0)
      writeChar('-'), x = -x;

    char s[24];
    int n = 0;
    while (x || !n)
      s[n++] = '0' + x % 10, x /= 10;
    while (n < output_len)
      s[n++] = '0';
    while (n--)
      writeChar(s[n]);
    if (end)
      writeChar(end);
  }

  inline void writeWord( const char *s ) {
    while (*s)
      writeChar(*s++);
  }

  inline void writeDouble( double x, int output_len ) {
    if (x < 0)
      writeChar('-'), x = -x;
    int t = (int)x;
    writeInt(t), x -= t;
    writeChar('.');
    for (int i = output_len - 1; i > 0; i--) {
      x *= 10;
      t = std::min(9, (int)x);
      writeChar('0' + t), x -= t;
    }
    x *= 10;
    t = std::min(9, (int)(x + 0.5));
    writeChar('0' + t);
  }
}
using namespace Input;


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

const int INF = 1e9 + 7;
struct Edge {
  int u, v, w;
};

int highest(int x) {
  return 31 - __builtin_clz(x);
//  for (int i = 31; i >= 0; i--) if (x & (1LL << i)) return i;
//  assert(0);
}

const int N = 200200;
const int K = 18;

vector<int> e[N];
int pr[N][K];
int mx[N][K];
ll up[N][K], down[N][K];
int h[N];

int getP(int v, int h) {
  assert(h >= 0);
  for (int i = 0; i < K; i++) if (h & (1 << i)) v = pr[v][i];
  return v;
};

const int UP = 0;
const int DOWN = 1;
ll go(int v, int ch, int cur, int dir) {
  //db3(v, ch, dir);
  if (ch == 0) return 0LL;

  ll res = 0;
  if (dir == UP) {
    for (int i = K - 1; i >= 0; i--) {
      if ((1 << i) <= ch && mx[v][i] <= cur) {
        res += (1LL << i) * cur;
        v = pr[v][i];
        ch -= 1 << i;
      }
    }
    if (ch > 0) {
      int k = highest(ch);
      res += up[v][k];
      cur = mx[v][k];
      v = pr[v][k];
      ch -= 1 << k;
      res += go(v, ch, cur, dir);
    }
  } else {
    int k = highest(ch);

    int need = 1 << k;
    int u = getP(v, ch - need);

    if (mx[u][k] <= cur) {
      return (1LL << k) * cur + go(v, h[v] - h[u], cur, dir);
    }

    for (int i = k - 1; i >= 0; i--) {
      if (mx[pr[u][i]][i] > cur) {
        u = pr[u][i];
      } else {
        res += (1LL << i) * cur;
      }
    }
    u = pr[u][0];
    ch = h[v] - h[u];
    assert(ch > 0);

    k = highest(ch);
    need = 1 << k;
    int nu = getP(v, ch - need);
    res += down[nu][k];
    res += go(v, h[v] - h[nu], mx[nu][k], dir);
  }

  return res;
};

vector<int> vct;
int par[N];
void dfs(int v, int pr) {
  vct.push_back(v);
  par[v] = pr;
  for (int to : e[v]) {
    if (to == pr) continue;
    dfs(to, v);
  }
};

vector<ll> fast(vector<Edge> ed, vector<pair<int, int>> q) {
  int n = ed.size() + 1;

  for (auto o : ed) {
    e[o.u].push_back(o.v);
    e[o.v].push_back(o.u);
  }

//  vector<int> par(n);
//  vector<int> vct;

  dfs(0, 0);

  const int K = 18;
  //vector<int> h(n);
  h[0] = 0;
  for (int i = 1; i < n; i++) {
    int v = vct[i];
    h[v] = h[par[v]] + 1;
    pr[v][0] = par[v];
    for (int j = 1; j < K; j++) pr[v][j] = pr[pr[v][j - 1]][j - 1];
  }


  auto lca = [&](int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    u = getP(u, h[u] - h[v]);
    if (u == v) return u;
    for (int i = K - 1; i >= 0; i--) {
      if (pr[u][i] != pr[v][i]) {
        u = pr[u][i];
        v = pr[v][i];
      }
    }
    return pr[u][0];
  };

  vector<int> a(n);
  for (auto o : ed) {
    if (par[o.u] == o.v) {
      swap(o.u, o.v);
    }
    assert(par[o.v] == o.u);
    a[o.v] = o.w;
  }

  for (int i = 0; i < n; i++) {
    int v = vct[i];
    mx[v][0] = a[v];
    for (int j = 1; j < K; j++) {
      mx[v][j] = max(mx[v][j - 1], mx[pr[v][j - 1]][j - 1]);
    }
  }

  auto getMX = [&](int v, int h) {
    int res = 0;
    for (int i = 0; i < K; i++) {
      if (h & (1 << i)) {
        res = max(res, mx[v][i]);
        v = pr[v][i];
      }
    }
    return res;
  };


  //vector<vector<ll>> up(n, vector<ll>(K));
  //vector<vector<ll>> down(n, vector<ll>(K));



  for (int v : vct) {
    up[v][0] = a[v];
    for (int j = 1; j < K; j++) {
      up[v][j] = up[v][j - 1];
      up[v][j] += go(pr[v][j - 1], 1 << (j - 1), mx[v][j - 1], UP);
    }

    down[v][0] = a[v];
    for (int j = 1; j < K; j++) {
      down[v][j] = down[pr[v][j - 1]][j - 1];
      down[v][j] += go(v, 1 << (j - 1), mx[pr[v][j - 1]][j - 1], DOWN);
    }
  }

  vector<ll> ans;
  for (auto o : q) {
    int u = o.first, v = o.second;
    int w = lca(u, v);

    ll res = 0;
    int cur = 0;

    int ch = h[u] - h[w];
    res += go(u, ch, cur, UP);
    cur = max(cur, getMX(u, ch));

    ch = h[v] - h[w];
    res += go(v, ch, cur, DOWN);
    ans.push_back(res);
  }
  return ans;
}

void print(vector<ll> v) {
  for (ll x : v) printf("%lld\n", x);
}

void test() {
  int n = 2e5;
  vector<Edge> ed(n - 1);
  for (int i = 0; i < n - 1; i++) {
    ed[i].u = i + 1;
    ed[i].v = rand() % (i + 1);
    ed[i].w = rand() % (int)1e9;
  }
  int q = 1e6;
  vector<pair<int, int>> qr(q);
  for (int i = 0; i < q; i++) {
    qr[i].first = qr[i].second = rand() % n;
    while (qr[i].second == qr[i].first) {
      qr[i].second = rand() % n;
    }
  }
  fast(ed, qr);
  //exit(0);
}




int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  //freopen("i.out", "w", stdout);
  //test();
#endif


  int n, q;
  //while (scanf("%d%d", &n, &q) == 2) {
  {
    n = readInt();
    q = readInt();
    vector<Edge> ed(n - 1);
    for (int i = 0; i < n - 1; i++) {
      //scanf("%d%d%d", &ed[i].u, &ed[i].v, &ed[i].w);
      ed[i].u = readInt();
      ed[i].v = readInt();
      ed[i].w = readInt();
      ed[i].u--;
      ed[i].v--;
    }
    vector<pair<int, int>> qr(q);
    for (int i = 0; i < q; i++) {
      //scanf("%d%d", &qr[i].first, &qr[i].second);
      qr[i].first = readInt();
      qr[i].second = readInt();

      qr[i].first--;
      qr[i].second--;
    }

    print(fast(ed, qr));
  }

  return 0;
}
