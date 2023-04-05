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

typedef int ll;
typedef long double ld;

const int maxn = 4.001e6, maxm = 2.001e6;
int N, M, S, T;
int max_h;

typedef unsigned int flow_t;
typedef unsigned int excess_t;

struct Edge {
  int to, next, id;
  void set(int _to, int _next, int _id){
    to=_to;
    next=_next;
    id = _id;
  }
};
Edge edges[2*maxm];
int edge_list_begin[maxn], lastEdge = 2;
inline void add_edge(int a, int b, int id) {
  b+=N;
  edges[lastEdge].set(b, edge_list_begin[a], id);
  edge_list_begin[a] = lastEdge++;
  edges[lastEdge].set(a, edge_list_begin[b], id);
  edge_list_begin[b] = lastEdge++;
}
int matchid[maxn];
int h[maxn], e[maxn], match[maxn], q[2*maxn], qbegin, qend, pushcnt;
inline void enqueue(int u) {
  if(qend == 2*maxn) qend=0;
  q[qend++]=u;
}
inline void pop() {
  ++qbegin;
  if(qbegin==2*maxn) qbegin=0;
}
inline void global_relabel(){
  int* qq = q;
  if(qend < maxn) qq = q+maxn;
  int l=0, r=0;
  fill(h, h+N+M, max_h);
  fill(match, match+N, -1);
  for(int i=N;i<N+M;++i){
    if(~match[i]) {
      match[match[i]] = i;
    } else {
      qq[r++]=i;
      h[i] = 0;
    }
  }
  while(l!=r){
    int u = qq[l++];
    for(int p = edge_list_begin[u];p;p = edges[p].next){
      int v = edges[p].to;
      if(h[v] == max_h){
        h[v] = h[u]+1;
        if(~match[v]){
          h[match[v]] = h[u]+2;
          qq[r++] = match[v];
        }   }   }   }
}
inline void init_matching() {
  fill(h, h + N, 1);
  fill(h+N, h+N+M, 0);
  fill(e, e+N, 1);
  fill(match, match+N+M, -1);
  qbegin = qend = 0;
  for(int i=0;i<N;++i){
    enqueue(i);
  }
  pushcnt = 0;
  max_h = N+M+5;
}
excess_t max_matching() {
  init_matching();
  while (qbegin!=qend) {
    if (clock() / (double)CLOCKS_PER_SEC > 3.2) break;
    int u = q[qbegin];
    int minh = max_h;
    for (int p = edge_list_begin[u]; p; p = edges[p].next) {
      int v = edges[p].to;
      minh = min(minh, h[v]+1);
      if (h[u] == h[v] + 1) {
        if(~match[v]){
          enqueue(match[v]);
          e[match[v]]=1;
        }
        match[v] = u;
        matchid[v] = edges[p].id;
        h[v]+=2;
        e[u]=0;
        pop();
        break;
      }
    }
    ++pushcnt;
    if (e[u]) {
      if(minh >= max_h){
        e[u]=0;
        pop();
      }
      h[u] = minh;
    }
    if(pushcnt == 2*N){
      global_relabel();
      pushcnt = 0;
    }
  }
  excess_t hits=0;
  for(int i=N;i<N+M;++i){
    if(~match[i]){
      ++hits;
      match[match[i]] = i;
    }
  }
  return hits;
}

void reset(int lsize, int rsize){
  N = lsize; M = rsize;
  lastEdge = 2;
  fill(edge_list_begin, edge_list_begin+N+M+4, 0);
}


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
inline void writeDouble( double x, int len = 0 ); // works correct only for |x| < 2^{63}
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
  assert(x <= (1LLU << 63) - 1);
  long long t = (long long)x;
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

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
#endif

  int n1, n2, m;
//  while (scanf("%d%d%d", &n1, &n2, &m) == 3) {
  {
    n1 = readInt();
    n2 = readInt();
    m = readInt();
    reset(n1, n2);

    vector<pair<pair<int, int>, int>> ed(m);
    for (int i = 0; i < m; i++) {
      int u, v;
//      scanf("%d%d", &u, &v);
      u = readInt();
      v = readInt();
      u--; v--;
      ed[i] = {{u, v}, i};
    }
//    mt19937 rnd;
    random_shuffle(ed.begin(), ed.end());
    for (auto o : ed) {
      int u = o.first.first;
      int v= o.first.second;
      add_edge(u, v, o.second);
    }

    int ans = max_matching();
    vector<int> res;
    vector<char> used(m);
    for (int i = N; i < N + M; i++) {
      if (~match[i]) {
        used[matchid[i]] = 1;
      }
    }
    for (int i = 0; i < m; ++i) if (used[i]) res.push_back(i + 1);
//    for (auto ed : gr.edges) {
//      if (ed.id >= 0 && ed.flow > 0) {
//        res.push_back(ed.id);
//      }
//    }
    assert((int)res.size() == ans);

    writeInt(ans, '\n');
    for (int d : res) {
      writeInt(d, '\n');
    }
//    printf("%d\n", ans);
//    for (int d : res) printf("%d\n", d);
  }

  return 0;
}
