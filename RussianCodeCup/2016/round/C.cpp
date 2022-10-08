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

#define TASKNAME "C"

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

vector<vector<int>> g;

void dfs(int v, int p, vector<int>& d) {
  for (int u : g[v]) {
    if (u != p) {
      d[u] = d[v] + 1;
      dfs(u, v, d);
    }
  }
}

const int MOD = 1000000007;

int ipow(int a, int b) {
  if (!b) return 1;
  if (b & 1) return (int)((ipow(a, b - 1) * 1LL * a) % MOD);
  int tmp = ipow(a, b / 2);
  return (int)((tmp * 1LL * tmp) % MOD);
}

void solve() {
  int n = readInt();
  g = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; i++) {
    int a = readInt();
    int b = readInt();
    a--, b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  vector<int> d0(n), d1(n), d2(n);
  dfs(0, -1, d0);
  int v1 = max_element(d0.begin(), d0.end()) - d0.begin();
  dfs(v1, -1, d1);
  int v2 = max_element(d1.begin(), d1.end()) - d1.begin();
  dfs(v2, -1, d2);

  int ans, ansv;
  ans = 1 << 30;
  ansv = -1;
  for (int i = 0; i < n; i++) {
    if (g[i].size() > 3) {
      printf("-1\n");
      return;
    }
    if (g[i].size() <= 2 && ans > max(d1[i], d2[i])) {
      ans = max(d1[i], d2[i]);
      ansv = i;
    }
  }
  if (ansv != -1) {
    int res = ipow(2, ans + 1);
    res -= n + 1;
    if (res < 0) res += MOD;
    printf("%d %d\n", ansv + 1, res);
  } else {
    printf("-1\n");
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
