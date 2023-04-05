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
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  vector<set<int>> a(m);

  for (int i = 0; i < m; i++) {
    int k;
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      int x;
      a[i].insert(x);
    }
  }

  sort(a.begin(), a.end(), [](const set<int>& a, const set<int>& b) -> bool {return a.size() > b.size();});
  vector<bool> good(m);

  for (int i = 0; i < m; i++) {
    for (int k = 0; k < i; k++) {
      bool ok = false;
      for (int x: a[i]) {
        if (a[k].find(x) == a[k].end()) ok = true;
      }
      if (ok) {
        good[i] = true;
      }
    }
  }

  vector<vector<bool>> g(m, vector<bool>(m));
  vector<int> d(m);
  for (int i = 0; i < m; i++) {
    if (!good[i]) continue;
    for (int j = i + 1; j < m; j++) {
      if (!good[j]) continue;
      for (int x : a[i]) {
        if (a[j].find(x) != a[j].end()) g[i][j] = g[j][i] = true;
      }
      if (g[i][j]) {
        d[i]++;
        d[j]++;
      }
    }
  }

  vector<bool> p(n);
  vector<int> res(n);
  int c = 0;

  for (int k = 0; k < m; k++) {
    for (int i = 0; i < m; i++) {
      if (good[i] && d[i] < 2) {
        for (int j = 0; j < m; j++) {
          if (g[i][j]) {
            for (int x : a[j]) {
              a[i].erase(x);
            }
          }
          d[j]--;
        }
        for (int x : a[i]) {
          if (!p[x]) {
            p[x] = true;
            res[x] = c++;
          }
        }
      }
    }
  }



  return 0;
}
