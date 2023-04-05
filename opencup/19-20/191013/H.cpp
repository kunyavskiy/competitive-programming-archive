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

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
  }

  ll ans = (1LL << 60);
  for (int ii = 0; ii <= n % 2; ++ii) {
    vector<int> p1, p2;
    vector<int> q1, q2;
    int X = (n / 2) + ii;
    for (int i = 0; i < n; ++i) {
      if (a[i] <= X) {
        p1.push_back(i);
      } else {
        q1.push_back(i);
      }
      if (b[i] >= n - X + 1) {
        p2.push_back(i);
      } else {
        q2.push_back(i);
      }
    }
    assert(p1.size() == p2.size());
    assert(q1.size() == q2.size());
    ll sum = 0;
    for (int i = 0; i < (int)p1.size(); ++i) {
      sum += abs(p1[i] - p2[i]);
    }
//    for (int i = 0; i < (int)p2.size(); ++i) {
//      sum += abs(q1[i] - q2[i]);
//    }
    ans = min(ans, sum);
  }
  printf("%lld\n", ans);

  return 0;
}
