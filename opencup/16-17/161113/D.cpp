#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "D"

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
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector <ll> vll;
typedef vector<int> vi;
typedef vector <vi> vvi;
typedef vector<bool> vb;
typedef vector <vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;

const int inf = 1e9;
const ld eps = 1e-9;
const int INF = inf;
const ld EPS = eps;

#ifdef LOCAL
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {
};
#endif

/*Template end*/

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt( T x );
inline void writeChar( int x );
inline void writeWord( const char *s );
inline void flush();

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
  while (c <= 32 && c != -1)
    c = getChar();
  return c;
}

template <class T>
inline T readInt() {
  int s = 1, c = readChar();
  if (c == -1) return 0;
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




int m;
vector<int> p;
vector<int> x, y, heap;
int heapSize;

void siftUp(int i) {
  while (i > 0 && y[heap[(i - 1) / 2]] < y[heap[i]]) {
    swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void insert(int i) {
  heap[heapSize++] = i;
  siftUp(heapSize - 1);
}

int removeMin() {
  int res = heap[0];
  heapSize--;
  heap[0] = heap[heapSize];
  int i = 0;
  while (2 * i + 1 < heapSize) {
    int j = i;
    if (y[heap[2 * i + 1]] > y[heap[j]]) {
      j = 2 * i + 1;
    }
    if (2 * i + 2 < heapSize && y[heap[2 * i + 2]] > y[heap[j]]) {
      j = 2 * i + 2;
    }
    if (i == j) break;
    swap(heap[i], heap[j]);
    i = j;
  }
  return res;
}


void solve() {
  while (true) {
    m = readInt();
    int n = readInt();
    if (m == 0) return;
    x = vector<int>(n);
    y = vector<int>(n);
    p = vector<int>(n);
    heap = vector<int>(n);
    for (int i = 0; i < n; i++) {
      x[i] = readInt();
      y[i] = readInt();
      p[i] = i;
    }
    if (n % 2 == 1) {
      writeInt(-1);
      writeChar('\n');
      continue;
    }
    long res = -1;
    for (int d = 0; d < 4; d++) {
      for (int i = 0; i < n; i++) {
        int t = x[i];
        x[i] = m - 1 - y[i];
        y[i] = t;
      }
      sort(p.begin(), p.end(), [](int a, int b) { return x[a] < x[b];});
      heapSize = 0;
      int t = m;
      for (int i = 0; i < n; i++) {
        if (y[p[i]] < t) {
          insert(p[i]);
        }
        if (i == n - 1 || x[p[i + 1]] > x[p[i]]) {
          while (heapSize > n / 2) {
            t = y[heap[0]];
            while (heapSize > 0 && y[heap[0]] == t) {
              removeMin();
            }
          }
          if (heapSize == n / 2) {
            long s = (x[p[i]] + 1) * 1l * (y[heap[0]] + 1);
            if (res == -1 || res > s) res = s;
          }
        }
      }
    }
    writeInt(res);
    writeChar('\n');
  }

}



/*private void sort(int l, int r) {
  if (r < l) return;
  int i = l;
  int j = r;
  int xx = p[(l + r) >> 1];
  while (j >= i) {
    while (x[p[i]] < x[xx]) i++;
    while (x[p[j]] > x[xx]) j--;
    if (i <= j) {
      int t = p[i];
      p[i] = p[j];
      p[j] = t;
      i++;
      j--;
    }
  }
  if (i < r) sort(i, r);
  if (l < j) sort(l, j);
}*/



int main() {
  #ifdef LOCAL
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
  #endif

  solve();
  flush();

  return 0;
}
