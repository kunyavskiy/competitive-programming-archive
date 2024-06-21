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

bool is_substring(vector<int> a, vector<int> b) {
  vector<int> p(a.size());
  for (int i = 1; i < (int)a.size(); i++) {
    int j = p[i-1];
    while (j && a[j] != a[i]) j = p[j-1];
    if (a[i] == a[j]) j++;
    p[i] = j;
  }
  int cur = 0;
  for (int x : b) {
    while (cur && a[cur] !=  x) cur = p[cur - 1];
    if (a[cur] == x) cur++;
    if (cur == (int)a.size()) return true;
  }
  return false;
}

int main() {
  #ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
  #endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> a(n * 2);
    vector<int> b(m);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      a[i + n] = a[i];
    }
    for (int& x : b) scanf("%d", &x);
    bool res = is_substring(b, a);
    reverse(b.begin(), b.end());
    res = res || is_substring(b, a);
    res = res && (b.size() < a.size());
    if (res) printf("1\n"); else printf("0\n");
  }

  return 0;
}
