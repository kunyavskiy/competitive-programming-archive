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
  freopen("j.in", "r", stdin);
//  freopen("j.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    struct seg {
      int l, r, c;
      bool operator< (const seg &s) const {
        if (l != s.l) return l < s.l;
        return r > s.r;
      }
    };
    vector<seg> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].c);
    }
    const int C = 1e6;
    a.push_back({0, C + 1, 0});
    n = a.size();

    sort(a.begin(), a.end());
    vector<int> vct;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      while (!vct.empty() && !(a[vct.back()].l <= a[i].l && a[i].r <= a[vct.back()].r)) {
        vct.pop_back();
      }
      if (!vct.empty()) {
        p[i] = vct.back();
      }
      vct.push_back(i);
    }
    vector<vector<int>> e(n);
    for (int i = 1; i < n; i++) e[p[i]].push_back(i);


    function<multiset<ll>(int)> dfs = [&](int v) {
      multiset<ll> st;
      for (int to : e[v]) {
        auto nw = dfs(to);
        if (st.size() < nw.size()) {
          st.swap(nw);
        }

        vector<ll> v1;
        while (!nw.empty()) {
          v1.push_back(*st.rbegin());
          st.erase(--st.end());
          v1.back() += *nw.rbegin();
          nw.erase(--nw.end());
        }
        st.insert(v1.begin(), v1.end());
      }
      st.insert(a[v].c);
//      dbv(st);
      return st;
    };
    auto st = dfs(0);
    vector<ll> ans(n + 1);
    for (int i = 1; i <= n; i++) {
      ll x = 0;
      if (!st.empty()) {
        x = *st.rbegin();
        st.erase(--st.end());
      }
      ans[i] = ans[i - 1] + x;
    }
    for (int i = 1; i < n; i++) printf("%lld%c", ans[i], " \n"[i + 1== n]);
  }

  return 0;
}
