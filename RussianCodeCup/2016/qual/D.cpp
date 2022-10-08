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

typedef long long ll;
typedef long double ld;

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


const int MAXC = 500100;
const int BUBEN = 1000;

ll cost[MAXC];

/*
const int SIZE = 1 << 26;

char mem[SIZE];
int memptr;
void* operator new(size_t x) {
  void* res = mem + memptr;
  memptr += x;
  assert(memptr <= SIZE);
  return res;
}

void operator delete(void*) {
  return;
}
 */

vector<int> divs[MAXC];

void init_divs(int a) {
  if (divs[a].empty()) {
    for (int i = 1; i*i <= a; i++) {
      if (a % i == 0) {
        divs[a].push_back(i);
        if (a / i != i) {
          divs[a].push_back(a / i);
        }
      }
    }
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

  vector<int> t(n);

  for (int i = 0; i < n; i++) {
    t[i] = readInt();
    int prev = -1;
    for (int j = 1; j <= BUBEN; j++) {
      int l = (t[i] + j - 1) / j;
      cost[j] += l;
      if (j <= MAXC / BUBEN + 1) {
        l = max(l, BUBEN + 1);
        cost[l] += j;
        if (j != 1) {
          cost[prev] -= j;
        }
      }
      prev = l;
    }
  }

  TIMESTAMP("read");

/*
  for (int i = 1; i < MAXC; i++) {
    for (int j = i; j < MAXC; j += i) {
      divs[j].push_back(i);
    }
  }
  TIMESTAMP("divs");
*/
  for (int i = BUBEN + 2; i < MAXC; i++)
    cost[i] += cost[i-1];

  for (int it = 0; it < m; it++) {
    int ty = readInt();
    int x = readInt();
    if (ty == 3) {
      writeInt(cost[x]);
      writeChar('\n');
    } else if (ty == 1) {
      x--;
      int a = t[x];
      t[x]++;
      init_divs(a);
      for (int i : divs[a]) {
        cost[i]++;
      }
    } else if (ty == 2) {
      x--;
      t[x]--;
      int a = t[x];
      init_divs(a);
      for (int i : divs[a]) {
        cost[i]--;
      }
    }
  }
  flush();

  return 0;
}
