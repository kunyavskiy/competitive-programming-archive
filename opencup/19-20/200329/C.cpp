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

typedef long long ll;
typedef long double ld;

int md(const string& a, int mod) {
  int res = 0;
  for (char c : a) {
    res = (res * 10 + c - '0') % mod;
  }
  return res;
}

char buf[1'100'000];

void solve() {
  int k;
  scanf("%s%d", buf, &k);
  string s = buf;
  if (s.size() <= 2) {
    int val = md(s, 1000);
    int a = 0;
    int b = 1;
    for (int i = 1; i < val; i++) {
      int c = (b * k + a) % val;
      a = b;
      b = c;
    }
    printf("%d\n", b);
    return;
  }

  k = k * k + 4;

  int m4 = (k % 4 == 1) || (md(s, 4) == 1);

  int v = md(s, k);
  assert(v);
  int ans = -1;
  for (int i = 0; i < k; i++) {
    if (i * i % k == v) {
      ans = 1;
    }
  }
  if (!m4) {
    ans *= -1;
  }

  if (ans == 1) {
    printf("%d\n", 1);
  } else {
    assert(s.back() != '0');
    s.back()--;
    printf("%s\n", s.data());
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) solve();

  return 0;
}
