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

map<int, vector<pair<int, int>>> g;
set<int> z;
int xx, yy;
int ee;

void dfs(int x, int pe) {
  z.insert(x);
  vector<pair<int, int>> &nb = g[x];
  if (nb.size() == 1) {
    xx = nb[0].first;
    ee = nb[0].second;
    yy = x;
//    cerr << xx << " " << yy << "\n";
  }
  for (auto y : nb) {
    if (z.count(y.first)) {
      if (pe != y.second) {
        xx = x;
        yy = y.first;
        ee = y.second;
//        cerr << xx << " " << yy << "\n";
      }
    } else {
      dfs(y.first, y.second);
    }
  }
}

void solve_test() {
  g.clear();
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back({y, i + 1});
    g[y].push_back({x, i + 1});
  }  
  z.clear();
  vector<int> x, y, e;
  for (auto &p : g) {
    if (z.count(p.first) == 0) {
      dfs(p.first, -1);
//      cerr << " " << xx << " " << yy << " " << ee << "\n";
      x.push_back(xx);
      y.push_back(yy);
      e.push_back(ee);
    }
  }
  cout << x.size() - 1 << "\n";
  for (int i = 1; i < (int)x.size(); i++) {
    cout << e[i] << " " << y[i] << " " << y[0] << "\n";
  }
}

int main() {
#ifdef LOCAL
  freopen("n.in", "r", stdin);
  freopen("n.out", "w", stdout);
#endif

  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) solve_test();

  return 0;
}
