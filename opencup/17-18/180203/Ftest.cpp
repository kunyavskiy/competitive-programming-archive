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

void precalc_check(int n) {
  vector<int> p(n);
  for (int i = 0; i < n / 2; i++) {
    p[i] = 2 * i;
    p[n / 2 + i] = 2 * i + 1;
  }
//  eprintf("n=%d\n", n);
//  for (int i = 0; i < n; i++)
//    eprintf("%d%c", p[i] + 1, "\n "[i + 1< n]);
  vector<bool> was(n);
  set<int> lens;
  int botva = 1;
  for (int i = 0; i < n; i++)
    if (!was[i]) {
      int l = 0;
      for (int x = i; !was[x]; x = p[x]) {
        was[x] = true;
        l++;
      }
      botva = botva * l / __gcd(botva, l);
      //eprintf("i=%d, l=%d, botva=%d\n", i, l, botva);
      lens.insert(l);
    }
  assert(botva == *--lens.end());
  for (int x : lens)
    assert(*--lens.end() % x == 0);
//  assert(lens.size() <= 2);
}

void precalc_check() {
  for (int n = 2; n <= 10000; n += 2)
    precalc_check(n);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

#ifdef LOCAL
  precalc_check();
#endif

  return 0;
}
