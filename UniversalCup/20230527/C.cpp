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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y)                                                              \
  cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z)                                                           \
  cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y   \
       << ", " << z << ")\n"
#define dbv(a)                                                                 \
  cerr << #a << " = ";                                                         \
  for (auto xxxx : a)                                                          \
    cerr << xxxx << " ";                                                       \
  cerr << endl

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

const int MAXN = 1'100'000;

int nxt[MAXN][26];
int cntf[MAXN];
bool is_good[MAXN];
char s[MAXN];
char ans[MAXN];

void solve() {
  int vs = 1;
  memset(nxt[0], -1, sizeof(nxt[0]));
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%s", s);
    int v = 0;
    for (int j = 0; s[j]; j++) {
      if (nxt[v][s[j] - 'a'] == -1) {
        memset(nxt[vs], -1, sizeof(nxt[vs]));
        cntf[vs] = 0;
        nxt[v][s[j] - 'a'] = vs++;
      }
      v = nxt[v][s[j] - 'a'];
    }
    cntf[v]++;
  }
  stack<int> q;
  q.push(0);
  int done = 0;
  while (!q.empty()) {
    int v = q.top(); q.pop();
    done += cntf[v];
    int sons = 0;
    for (int i = 25; i >= 0; i--) {
      if (nxt[v][i] != -1) {
        q.push(nxt[v][i]);
        sons++;
      }
    }
    if (sons + cntf[v] >= 2 && done + (int)q.size() >= k) {
      is_good[v] = true;
    } else {
      is_good[v] = false;
    }
  }
  auto find = [](auto find, int v, int pt) -> bool {
    if (is_good[v]) {
      ans[pt] = 0;
      return true;
    }
    for (int i = 0; i < 26; i++) {
      if (nxt[v][i] != -1) {
        ans[pt] = i + 'a';
        if (find(find, nxt[v][i], pt + 1)) {
          return true;
        }
      }
    }
    return false;
  };
  find(find, 0, 0);
  if (ans[0] == 0) {
    strcpy(ans, "EMPTY");
  }
  printf("%s\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    solve();
  }

  return 0;
}
