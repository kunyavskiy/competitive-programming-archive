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

vector<vector<int>> g;
vector<int> w;
int center;

int find_center(int x, int p) {
  int s = w[x];
  for (int y : g[x]) {
    if (y == p) continue;
    s += find_center(y, x);
  }
  if (s == 2) {
    center = x;
  }
  return s;
}

vector<int> h;
vector<int> p;
void build_h(int x, int p) {
  for (int y : g[x]) {
    if (y == p) continue;
    h[y] = h[x] + 1;
    ::p[y] = x;
    build_h(y, x);
  }
}

bool go(int a, int b, vector<pair< int, int>> &res) {
  int lca;
  {
    int aa = a;
    int bb = b;
    while (aa != bb) {
      if (h[aa] > h[bb]) aa = p[aa]; else bb = p[bb];
    }
    lca = aa;
  }
  int n = g.size();
  vector<int> op(n, -1);
  vector<int> prev(n, -1);
  op[a] = b; op[b] = a;
  vector<int> q;
  q.push_back(a);
  q.push_back(b);
  while (!q.empty()) {
    int x = q.back();
    q.pop_back();
    if (op[op[x]] == -1) {
      op[op[x]] = x;
      prev[op[x]] = x;
      q.push_back(op[x]);
    }
    if (op[x] == lca) break;
    for (int y : g[x]) {
      if (y != p[x] && op[y] == -1) {
        int z = p[op[x]];
        op[y] = z;
//        op[z] = y;
        prev[y] = x;
//        prev[z] = op[x];
        q.push_back(y);
//        q.push_back(z);
      }
    }
  }
  if (op[lca] == -1) {
    return false;
  }
  int x = lca;
  int y = op[x];
  res.push_back({x, y});
  bool rev = false;
  while (prev[x] != -1) {
    int xx = prev[x];
    int yy = op[xx];
    if (xx == y && yy == x) {
      rev = !rev;
    } else {
      if (!rev)
        res.push_back({xx, yy});
      else
        res.push_back({yy, xx});
    }
    x = xx; y = yy;
  }
  reverse(res.begin(), res.end());
  while (res.back().first != center) {
    res.push_back({p[res.back().first], p[res.back().second]});
  }
  return true;
}

void solve_test() {
  int n;
  scanf("%d", &n);
  g.clear();
  g.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  a--; b--; c--; d--;
  w.clear();
  w.resize(n);
  w[a] = w[b] = w[c] = w[d] = 1;
  center = -1;
  find_center(0, -1);
  assert(center != -1);
  h.clear();
  h.resize(n);
  p.clear();
  p.resize(n);
  h[0] = 0; p[0] = -1;
  build_h(center, -1);

  vector<pair< int, int>> res1;
  vector<pair< int, int>> res2;
  if (go(a, b, res1) && go(c, d, res2)) {
    vector<pair< int, int>> res;
    for (auto p: res1) {
      res.push_back(p);
    }

    int k = h[res.back().second] - 1;
    vector<pair< int, int>> res3(k);
    int x = res.back().second;
    for (int i = 0; i < k; i++) {
      x = p[x];
      res3[i].second = x;
    }
    x = res2.back().second;
    for (int i = 0; i < k; i++) {
      x = p[x];
      res3[k - 1 - i].first = x;
    }
    for (auto p: res3) {
      res.push_back(p);
    }

    reverse(res2.begin(), res2.end());
    for (auto p: res2) {
      res.push_back({p.second, p.first});
    }

    deque<int> worm;
    {
      vector<int> aa = {a};
      vector<int> bb = {b};
      while (aa.back() != bb.back()) {
        if (h[aa.back()] > h[bb.back()]) aa.push_back(p[aa.back()]);
        else bb.push_back(p[bb.back()]);
      }
      bb.pop_back();
      reverse(bb.begin(), bb.end());
      for (int x : aa) {
        worm.push_back(x);
      }
      for (int x : bb) {
        worm.push_back(x);
      }
    }
    if (worm.front() != res[0].first) {
      reverse(worm.begin(), worm.end());
    }
    cout << res.size() - 1 << "\n";
    for (int i = 1; i < (int)res.size(); i++) {
      if (worm[1] == res[i].first) {
        worm.pop_front();
        worm.push_back(res[i].second);
        cout << res[i].second + 1 << " ";
      } else {
        worm.pop_back();
        worm.push_front(res[i].first);
        cout << res[i].first + 1 << " ";
      }
    }
    cout << "\n";

//    for (auto p : res) {
//      cout << p.first + 1 << "-" << p.second + 1 << " ";
//    }
//    cout << "\n";
  } else {
    cout << "-1\n";
  }
  
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) solve_test();
  
  return 0;
}
