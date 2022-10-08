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

void solve() {
  int n;
  string a, b, c;
  cin >> n >> a >> b >> c;
  eprintf("%d\n%s\n%s\n%s\n", n, a.c_str(), b.c_str(), c.c_str());
  a = a + a;
  b = b + b;
  c = c + c;
  auto test_one = [](const string& a, const string& b) {
    int pt = 0;
    for (char c : a) {
      if (b[pt] == c) pt++;
      if (pt == (int)b.size()) return true;
    }
    return false;
  };
  auto test = [&](const string &t) {
    return test_one(a, t) && test_one(b, t) && test_one(c, t);
  };

  for (char c1 = '0'; c1 <= '1'; c1++) {
    for (char c2 = '0'; c2 <= '1'; c2++) {
      for (char c3 = '0'; c3 <= '1'; c3++) {
        string cand = string(n, c1) + c2 + string(n, c3);
        if (test(cand)) {
          printf("%s\n", cand.c_str());
          return;
        }
        cand = string(n, c1) + string(n, c3) + c2;
        if (test(cand)) {
          printf("%s\n", cand.c_str());
          return;
        }
        cand = c2 + string(n, c1) + string(n, c3);
        if (test(cand)) {
          printf("%s\n", cand.c_str());
          return;
        }
      }
    }
  }
  assert(false);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  cin >> t;
  while (t-->0) {
    solve();
  }

  return 0;
}
