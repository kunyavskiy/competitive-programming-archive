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
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<pair<int, int>> next(n);
  vector<pair<int, int>> first;

  ll s = 0;

  for (int i = 0; i < m; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    x--; y--;
    s += z;
    if (x == 0) {
      first.push_back({y, z});
    } else {
      next[x] = {y, z};
    }
  }

  vector<vector<ll>> a;

  for (auto &p : first) {
    vector<ll> q;
    q.push_back(p.second);
    int x = p.first;
    while (x != n - 1) {
      q.push_back(next[x].second);
      x = next[x].first;
    }
    sort(q.begin(), q.end());
    a.push_back(q);
  }

  n = a.size();
  m = a[0].size();

//  for (auto q : a) {
//    for (auto x : q) {
//      cerr << x << " ";
//    }
//    cerr << "\n";
//  }

  s /= m;

  vector<ll> d(n);

  set<pair<int, int>> st;
  for (int i = 0; i < n; i++) {
    st.insert({0, i});
  }

  ll res = 0;

  while (s > 0) {
    auto f = *st.begin();
    ll x = min(s, (ll)a[f.second][f.first] - d[f.second]);
    res += x * f.first;
    s -= x;
    d[f.second] += x;
    st.erase(f);
    f.first++;
    st.insert(f);
  }

  cout << res << "\n";

  return 0;
}
