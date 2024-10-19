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
#include <numeric>
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

bool query(int a, int b) {
  printf("? %d %d\n", a + 1, b + 1);
  fflush(stdout);
  char c;
  scanf(" %c", &c);
  return c == 'R';
}

int main() {
#ifdef LOCAL
  //freopen("i.in", "r", stdin);
  //freopen("i.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  set<int> r, b;
  vector<pair<int, int>> re, be;
  r.insert(0);
  b.insert(0);
  for (int i = 1; i < n; i++) {
    auto &conn = (r.size() == 1) ? r : b;
    auto &nconn = (r.size() == 1) ? b : r;
    auto &conne = (r.size() == 1) ? re : be;
    auto &nconne = (r.size() == 1) ? be : re;
    bool in_conn = (r.size() == 1);
    auto it = nconn.begin();
    while (true) {
      if (it == nconn.end()) {
        conn.insert(i);
        nconn.insert(i);
        break;
      } else if (query(*it, i) == in_conn) {
        conne.emplace_back(*it, i);
        nconn.insert(i);
        break;
      } else {
        nconne.emplace_back(*it, i);
        it = nconn.erase(it);
      }
    }
    assert(conn.size() == 1 || nconn.size() == 1);
    assert((int)conn.size() + (int)conne.size() == i + 1);
    assert((int)nconn.size() + (int)nconne.size() == i + 1);
  }

  const auto& ans = (r.size() == 1) ? re : be;
  printf("!\n");
  for (auto [x, y] : ans) {
    printf("%d %d\n", x + 1, y + 1);
  }
  return 0;
}
