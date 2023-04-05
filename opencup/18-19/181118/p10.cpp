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
  freopen("p10.in", "r", stdin);
  //freopen("p10.out", "w", stdout);
#endif

  int n, m, l;
  while (scanf("%d%d%d", &n, &m, &l) == 3) {
    vector<pair<pair<int, int>, int>> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &a[i].first.first, &a[i].first.second);
      a[i].second = i;
    }
    vector<pair<int, int>> b(m);
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &b[i].first, &b[i].second);
    }

    ll ans = 0;
    sort(a.begin(), a.end());
    vector<pair<int, int>> v1, v2;
    for (int i = 0; i < (int)b.size(); i++) {
      int k = min(b[i].first, b[i].second);
      b[i].first -= k;
      b[i].second -= k;
      ans += 2LL * l * k;
      if (b[i].first > 0) {
        v1.push_back({b[i].first, i});
      } else {
        v2.push_back({b[i].second, i});
      }
    }
    sort(v1.begin(), v1.end());
    reverse(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    reverse(v2.begin(), v2.end());

    vector<int> c;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < a[i].first.second; j++) {
        c.push_back(i);
        assert(c.size() <= (int)2e6);
      }
    }

    int L = 0, R = (int)c.size() - 1;
    vector<vector<int>> res(n);
    for (auto o : v1) {
      ans += 1LL * o.first * 2 * a[c[L]].first.first;
      res[a[c[L]].second].push_back(o.second);
      L++;
    }
    for (auto o : v2) {
      ans += 1LL * o.first * 2 * (l - a[c[R]].first.first);
      res[a[c[R]].second].push_back(o.second);
      R--;
    }

    printf("%lld\n", ans);
    for (int i = 0; i < n; i++) {
      printf("%d", (int)res[i].size());
      for (int id : res[i]) printf(" %d", id + 1);
      printf("\n");
    }
  }

  return 0;
}
