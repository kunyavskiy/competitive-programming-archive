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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

typedef long long ll;
typedef long double ld;

unsigned s;

unsigned getNext() {
  s ^= s << 13;
  s ^= s >> 17;
  s ^= s << 5;
  return s;
}

typedef unsigned long long ull;
const ull UINF = static_cast<ull>(-1);

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d%u", &n, &m, &s) == 3) {
    vector<pair<ull, int>> minvs(n, make_pair(UINF, -1));
    for (int i = 0; i < m; i++) {
      int u = getNext() % n;
      int v = getNext() % n;
      ull w = getNext() / 4;
      w *= getNext();
      #ifdef LOCAL
      eprintf("%d %d %llu\n", u, v, w);
      #endif
      if (u != v) {
        pair<ull, int> p(w, i);
        minvs[u] = min(minvs[u], p);
        minvs[v] = min(minvs[v], p);
      }
    }
    vector<unsigned> res((m + 31) / 32);
    for (auto e : minvs) {
      if (e.second >= 0) {
        //eprintf("take edge %d (w=%llu)\n", e.second, e.first);
        res[e.second / 32] |= 1u << (e.second % 32);
      }
    }
    for (size_t i = 0; i < res.size(); i++)
      printf("%u%c", res[i], "\n "[i + 1 < res.size()]);
  }

  return 0;
}
