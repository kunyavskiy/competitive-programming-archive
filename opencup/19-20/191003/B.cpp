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
  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    vector<int> b(k);
    for (int i = 0; i < n; i++) b[a[i] - 1]++;
    sort(b.begin(), b.end());

    int L = b[k - 1];
    int R = b[k - 1] + b[k / 2];

    set<pair<int, int>> st;

    auto f = [&](int bus) {
      vector<char> taken(k);
      int j = -1;
      int z = 0;
      int ans = 0;
      for (int i = k - 1; i >= 0; i--) {
        if (taken[i]) continue;
        while (j + 1 < i && !taken[j + 1] && b[i] + b[j + 1] <= bus) {
          j++;
        }
        while (z < i && taken[z]) z++;

        ans++;
        taken[i] = 1;
        if (0 <= j && j < i && !taken[j]) {
          taken[j] = 1;
        } else if (z < i && !taken[z] && b[z] + b[i] <= bus) {
          taken[z] = 1;
        }
      }
      return ans;
    };
    st.insert({L, f(L)});
    st.insert({R, f(R)});
    function<void(int, int)> rec = [&](int l, int r) {
      if (r - l < 2) return;
      int m = (l + r) >> 1;
      auto it = st.lower_bound({m, -1});
      auto pit = it--;
      if (pit->second == it->second) return;
      st.insert({m, f(m)});
      rec(l, m);
      rec(m, r);
    };
    rec(L, R);
    ll ans = 1e18;
    for (auto it : st) ans = min(ans, 1LL * it.first * it.second);
    cout << ans << endl;
  }

  return 0;
}
