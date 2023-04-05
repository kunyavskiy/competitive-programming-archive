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

struct dsu {
  vector<int> p;
  vector<int> id;
  explicit dsu(int n) : p(n), id(n) {
    for (int i = 0; i < n; i++) {
      p[i] = i;
    }
  }
  int get(int x) {
    if (p[x] == x) return x;
    return p[x] = get(p[x]);
  }
  int join(int a, int b) {
    a = get(a);
    b = get(b);
    p[a] = b;
    return b;
  }
  void setId(int a, int nid) {
    id[get(a)] = nid;
  }
  int getId(int a) { return id[get(a)]; }
};

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    dsu d(n);
    for (int i = 0; i < n; i++) {
      d.setId(i, i);
    }
    vector<int> l(n), r(n, 1);
    vector<vector<pair<int, int>>> as(n);// X = first + second
    vector<vector<pair<int, int>>> bs(n);// X = first - second;

    for (int i = 0; i < m; i++) {
      int ty;
      scanf("%d", &ty);
      if (ty == 1) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        int ida = d.getId(a);
        int idb = d.getId(b);
        d.join(a, b);
        int idn = l.size();
        l.push_back(0);
        r.push_back(n);
        as.emplace_back();
        bs.emplace_back();
        d.setId(a, idn);
        eprintf("x%d = x%d + x%d\n", idn, ida, idb);
        as[idn].emplace_back(ida, idb);
        bs[ida].emplace_back(idn, idb);
        bs[idb].emplace_back(idn, ida);
      } else if (ty == 2) {
        int a;
        scanf("%d", &a);
        --a;
        int ida = l.size();
        int idn = d.getId(a);
        int idb = a;
        eprintf("x%d = x%d + x%d\n", idn, ida, idb);
        d.setId(a, l.size());

        l.push_back(0);
        r.push_back(n);
        as.emplace_back();
        bs.emplace_back();

        as[idn].emplace_back(ida, idb);
        bs[ida].emplace_back(idn, idb);
        bs[idb].emplace_back(idn, ida);
      } else if (ty == 3) {
        int a, lf, rg;
        scanf("%d%d%d", &a, &lf, &rg);
        --a;
        int ida = d.getId(a);
        eprintf("ida = %d\n", ida);
        l[ida] = max(l[ida], lf);
        r[ida] = min(r[ida], rg);
      }
    }

    auto push = [&]() -> bool {
      queue<int> q;
      vector<int> inq(l.size());
      for (int i = 0; i < (int)l.size(); i++) {
        inq[i] = true;
        q.push(i);
      }
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        inq[v] = false;
        int oldl = l[v];
        int oldr = r[v];

        for (auto [b, c] : as[v]) {
          l[v] = max(l[v], l[b] + l[c]);
          r[v] = min(r[v], r[b] + r[c]);
        }
        for (auto [b, c] : bs[v]) {
          l[v] = max(l[v], l[b] - r[c]);
          r[v] = min(r[v], r[b] - l[c]);
        }
        eprintf("%d: [%d, %d]\n", v, l[v], r[v]);
        if (l[v] > r[v]) return false;
        if (l[v] != oldl || r[v] != oldr) {
          for (auto [b, c] : as[v]) {
            if (!inq[b]) { q.push(b); inq[b] = true; }
            if (!inq[c]) { q.push(c); inq[c] = true; }
          }
          for (auto [b, c] : bs[v]) {
            if (!inq[b]) { q.push(b); inq[b] = true; }
            if (!inq[c]) { q.push(c); inq[c] = true; }
          }
        }
      }
      return true;
    };

//    for (int i = 0; i < (int)l.size(); i++) {
//      eprintf("%d: [%d, %d]\n", i, l[i], r[i]);
//    }
//    eprintf("==\n");

    if (!push()) {
      printf("NO\n");
      continue;
    }
    string ans;
    for (int i = 0; i < n; i++) {
      if (l[i] != r[i]) {
        vector<int> lb = l, rb = r;
        r[i] = 0;
        if (!push()) {
          eprintf("????");
          l = lb;
          r = rb;
          l[i] = 1;
          bool rr = push();
          if (!rr) {
            printf("NO\n");
            return 0;
          }
        }
      }
      if (l[i] == 0) {
        ans += "B";
      } else {
        ans += "R";
      }
    }
    printf("YES\n%s\n", ans.c_str());
  }

  return 0;
}
