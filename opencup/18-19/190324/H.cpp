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

struct edge {
  int a, b;
  int w;

  edge(int a, int b, int w) : a(a), b(b), w(w) {}
  edge() {}
};

vector<int> dsu;

int get(int x) {
  if (dsu[x] == x) return x;
  return dsu[x] = get(dsu[x]);
};

bool join(int a, int b) {
  a = get(a);
  b = get(b);
  if (a == b) return false;
  dsu[a] = b;
  return true;
};


int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &a[i][j]);
      }
    }

    vector<edge> es;

    for (int i = 0; i < n; i++) {
      vector<pair<int, int>> v(m);
      for (int j = 0; j < m; j++) {
        v[j] = {a[i][j], i * m + j};
      }
      sort(v.begin(), v.end());
      for (int j = 1; j < m; j++) {
        es.emplace_back(v[j - 1].second, v[j].second, v[j].first - v[j - 1].first);
      }
    }

    for (int j = 0; j < m; j++) {
      vector<pair<int, int>> v(n);
      for (int i = 0; i < n; i++) {
        v[i] = {a[i][j], i * m + j};
      }
      sort(v.begin(), v.end());
      for (int i = 1; i < n; i++) {
        es.push_back({v[i - 1].second, v[i].second, v[i].first - v[i - 1].first});
      }
    }

    sort(es.begin(), es.end(), [](const edge& a, const edge& b) { return a.w < b.w;});

    ll ans = 0;

    dsu = vector<int>(n * m);
    for (int i = 0; i < n * m; i++) {
      dsu[i] = i;
    }

    for (edge e : es) {
      if (join(e.a, e.b)) {
        ans += e.w;
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}
