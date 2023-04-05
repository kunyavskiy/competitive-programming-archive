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
  freopen("p1.in", "r", stdin);
  freopen("p1.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  vector<ll> sp(n);
  vector<ll> ss(n);
  sp[0] = 1;
  for (int i = 0; i < n - 1; i++) {
    sp[i + 1] = max(min(sp[i] * a[i], (ll)2e9), -(ll)2e9);
  }
  ss[n - 1] = 1;
  for (int i = n - 1; i > 0; i--) {
    ss[i - 1] = max(min(ss[i] * a[i], (ll)2e9), -(ll)2e9);
  }

  for (int i = 0; i < n; i++) {
    if (a[i] == ss[i] * sp[i]) {
      cout << "Yes\n" << a[i] << "\n";
      return 0;
    }
  }
  cout << "No\n";

  return 0;
}
