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
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> x(n), a(n), b(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &x[i], &a[i], &b[i]);
  }
  vector<int> v;
  for (int i = 0; i < n; i++) {
    v.push_back(a[i]);
    v.push_back(b[i]);
  }
  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());
  int m = v.size();

  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    b[i] = lower_bound(v.begin(), v.end(), b[i]) - v.begin();
  }

  vector<int> c(m);
  for (int i = 0; i < n; i++) {
    c[a[i]]++;
    c[b[i]]--;
  }

  for (int i = 1; i < m; i++) {
    c[i] += c[i - 1];
  }

  const int N = 1 << 18;
  vector<ll> d(N);
  for (int i = 0; i < m - 1; i++) {
    d[c[i]] += v[i + 1] - v[i];
  }
  for (int i = N - 2; i >= 0; i--) {
    d[i] += d[i + 1];
  }
  for (int i = N - 2; i >= 0; i--) {
    d[i] += d[i + 1];
  }

  int q;
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%lld\n", d[l + r + 3]);
  }

  return 0;
}
