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
#include <numeric>

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

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> d(n - k + 1);
  for (int &x : d) {
    scanf("%d", &x);
    x -= k;
  }
  vector<ll> v(n);
  for (int i = k; i < n; i++) {
    v[i] = v[i - k] + d[i - k + 1] - d[i - k];
  }
  vector<int> mid(k);
  vector<int> order(k);
  for (int i = 0; i < k; i++) {
    order[i] = i;
    mid[i] = i;
    for (int j = i; j < n; j += k) {
      if (v[mid[i]] > v[j]) {
        mid[i] = j;
      }
    }
    ll shift = -v[mid[i]];
    for (int j = i; j < n; j += k) {
      v[j] += shift;
    }
  }
  vector<vector<int>> ans;
  do {
    vector<int> cur(n);
    vector<bool> used(n);
    int pt = 0;
    bool fail = false;
    for (int i = 0; i < n && !fail; i++) {
      if (!used[i]) {
        for (int j = order[pt++]; j < n; j += k) {
          ll val = i + v[j];
          if (!(0 <= val && val < n) || used[val]) {
            fail = true;
            break;
          }
          cur[j] = val;
          used[val] = true;
        }
      }
    }
    for (int i = 0; i + k <= n; i++) {
      if (accumulate(cur.begin() + i, cur.begin() + i + k, 0LL) != d[i]) {
        fail = true;
      }
    }
    if (!fail) {
      ans.push_back(std::move(cur));
    }
  } while (next_permutation(order.begin(), order.end()));
  sort(ans.begin(), ans.end());

  printf("%d\n", (int)ans.size());
  for (const auto&x : ans) {
    for (int y : x) {
      printf("%d ", y + 1);
    }
    printf("\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();


  return 0;
}
