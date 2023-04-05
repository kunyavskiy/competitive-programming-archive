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

vector<vector<pair<int, pair<int, int>>>> g;
vector<ll> s1;

void dfs1(int x, int p) {
  if (g[x].size() == 1) {
    s1[x] += 1000000;
  }
  for (auto &e : g[x]) {
    if (e.first == p) continue;
    dfs1(e.first, x);
    s1[x] += min(s1[e.first], (ll)e.second.second);
  }
}

vector<ll> s2;

void dfs2(int x, int p) {
  for (auto &e : g[x]) {
    if (e.first == p) continue;
    s2[e.first] = min(s2[x] + s1[x] - min(s1[e.first], (ll)e.second.second), (ll)e.second.first);
    dfs2(e.first, x);
  }
}

int main() {
#ifdef LOCAL
  freopen("p11.in", "r", stdin);
  freopen("p11.out", "w", stdout);
#endif

  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  g.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y, cx, cy;
    cin >> x >> y >> cx >> cy;
    x--; y--;
    g[x].push_back({y, {cx, cy}});
    g[y].push_back({x, {cy, cx}});
  }

  s1.resize(n);
  dfs1(0, -1);
  s2.resize(n);
  dfs2(0, -1);

  for (int i = 0; i < n; i++) {
//    cout << s1[i] << " " << s2[i] << "\n";
    ll res = s1[i] + s2[i];
    if (g[i].size() == 1) res -= 1000000;
    cout << res << "\n";
  }

  return 0;
}
