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
typedef pair<int, int> pii;

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n, hmin, hmax;
  scanf("%d%d%d", &n, &hmin, &hmax);
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a.begin(), a.end());
  for (int x : a) {
    eprintf("%d ", x);
  }
  eprintf("\n");

  vector<pii> diffs;
  for (int i = 1; i < n; ++i) {
    diffs.push_back({a[i] - a[i - 1], i - 1});
  }
  sort(diffs.begin(), diffs.end());

  vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    p[i] = i;
  }

  int xor_sum = (n & 1);
  int min_border = 0;
  for (int i = 0; i < n - 1; ++i) {
#ifdef LOCAL
    int xor2 = 0;
    for (int j = 0; j < n;) {
      xor2 ^= (p[j] - j + 1);
      eprintf("%d..%d ", j, p[j]);
      j = p[j] + 1;
    }
    eprintf("\n");
    assert(xor2 == xor_sum);
#endif
    int max_border = diffs[i].first;
    int index = diffs[i].second;
    eprintf("index %d diff %d : xor %d h=[%d..%d)\n", index, max_border, xor_sum, min_border, max_border);
    if (xor_sum == 0) {
      int ans = max(hmin, min_border);
      if (ans <= max_border && ans <= hmax) {
        printf("%d\n", ans);
        return 0;
      }
    }

    min_border = max_border + 1;
    int L = p[index];
    int R = p[index + 1];
    xor_sum ^= ((index - L + 1) ^ (R - index) ^ (R - L + 1));
    p[L] = R;
    p[R] = L;
  }

  if (xor_sum == 0) {
    int ans = max(hmin, min_border);
    if (ans <= hmax) {
      printf("%d\n", ans);
      return 0;
    }
  }

  printf("-1\n");

  return 0;
}
