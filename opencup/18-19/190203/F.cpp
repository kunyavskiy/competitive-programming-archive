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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<set<int>> v(n);
    vector<vector<int>> vv(n);
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &a[i], &b[i]);
      --a[i], --b[i];
      v[a[i]].insert(i);
      v[b[i]].insert(i);
      vv[a[i]].push_back(i);
      vv[b[i]].push_back(i);
    }
    set<int> q;
    vector<int> from_larger(m);
    from_larger[0] = 1;

    ll ans = 0;

    auto come = [&](int x) {
      q.insert(x);
      v[a[x]].erase(x);
      v[b[x]].erase(x);
      ans += (vv[a[x]].end() - upper_bound(vv[a[x]].begin(), vv[a[x]].end(), x)) * 1LL * (x + 1);
      ans += (vv[b[x]].end() - upper_bound(vv[b[x]].begin(), vv[b[x]].end(), x)) * 1LL * (x + 1);
      if (from_larger[x]) {
        ans -= (x + 1);
      }
    };

    come(0);

    while (!q.empty()) {
      int x = *q.begin();
      q.erase(x);
      while (true) {
        int id = m;
        int s = a[x];
        int t = b[x];
        if (!v[s].empty()) {
          id = min(id, *v[s].begin());
        }
        if (!v[t].empty()) {
          id = min(id, *v[t].begin());
        }
        if (id == m) {
          break;
        }
        if (id < x) {
          ans += x + 1;
          from_larger[id] = 1;
          come(id);
          q.insert(x);
          break;
        } else {
          come(id);
        }
      }
    }
    printf("%lld\n", ans);
  }

  return 0;
}
