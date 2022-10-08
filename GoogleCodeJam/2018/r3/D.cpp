#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

struct point {
  int x, y;
  point() : x(0), y(0) {}
  point(int x, int y) : x(x), y(y) {}
  point operator+(const point &p2) const { return point(x + p2.x, y + p2.y); }
  point operator-(const point &p2) const { return point(x - p2.x, y - p2.y); }
  ll operator*(const point &p2) const { return ll(x) * p2.y - ll(y) * p2.x; }
  ll operator^(const point &p2) const { return ll(x) * p2.x + ll(y) * p2.y; }
  bool operator==(const point &p2) const { return x == p2.x && y == p2.y; }

  int side() {
    return y > 0 || (y == 0 && x > 0);
  }
};

bool operator<(const point &lhs, const point &rhs) {
  if (lhs.x < rhs.x)
    return true;
  if (rhs.x < lhs.x)
    return false;
  return lhs.y < rhs.y;
}


void PreCalc() {
}

map<point, int> idgen;
vector<vector<pair<int, int>>> g;
vector<point> pt;

int getId(const point& p) {
  if (idgen.find(p) == idgen.end()) {
    int id = idgen.size();
    idgen[p] = id;
    pt.push_back(p);
    g.push_back({});
  }
  return idgen[p];
}

struct Sorter {
  point center;

  bool operator()(const pair<int,int>& a,const pair<int, int>& b) const {
    point p1 = pt[a.first] - center;
    point p2 = pt[b.first] - center;
    if (p1.side() != p2.side()) {
      return p1.side() < p2.side();
    }
    return p1 * p2 > 0;
  }
};

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  idgen.clear();
  g.clear();
  pt.clear();

  for (int i = 0; i < n; i++) {
    point a, b;
    scanf("%d%d%d%d", &a.x, &a.y, &b.x, &b.y);
    int aid = getId(a);
    int bid = getId(b);
//    eprintf("%d %d\n", aid, bid);
    g[aid].push_back({bid, i});
    g[bid].push_back({aid, i});
  }

  vector<vector<bool>> gused(g.size());

  for (int i = 0; i < (int)g.size(); i++) {
    sort(g[i].begin(), g[i].end(), Sorter{pt[i]});
    gused[i].resize(g[i].size());
//    eprintf("%d %d:", pt[i].x, pt[i].y);
//    for (auto j : g[i]) {
//      eprintf(" (%d,%d)", pt[j.first].x, pt[j.first].y);
//    }
//    eprintf("\n");
  }

  vector<vector<int>> egs(n);
  vector<vector<int>> gs;

  for (int i = 0; i < (int)g.size(); i++) {
    for (int j = 0; j < (int)g[i].size(); j++) {
      if (!gused[i][j]) {
        gs.push_back({});
        int curv = i;
        int cure = j;
        while (!gused[curv][cure]) {
//          eprintf("->(%d, %d)", pt[curv].x, pt[curv].y);
          int eid = g[curv][cure].second;
          gs.back().push_back(eid);
          egs[eid].push_back(gs.size() - 1);
          gused[curv][cure] = true;
          int nextv = g[curv][cure].first;
          int nexte = find(g[nextv].begin(), g[nextv].end(), pair<int, int>{curv, eid}) - g[nextv].begin();
          assert(nexte != (int)g[nextv].size());
          nexte = (nexte + 1) % (g[nextv].size());
          curv = nextv;
          cure = nexte;
        }
//        eprintf("\n");
      }
    }
  }

  for (int first = 0; first < (int)gs.size(); first++) {
    set<int> s(gs[first].begin(), gs[first].end());
    vector<bool> used(gs.size());
    vector<bool> usede(n);
    used[first] = true;
    vector<int> res;
    int kk = k - 1;
    while (s.size()) {
      int id = *s.rbegin();
      if (usede[id]) {
        s.erase(id);
        continue;
      }
      usede[id] = true;
      if (id == kk) kk--;
      if (id <= kk) break;
      s.erase(id);
      for (int g : egs[id]) {
        if (!used[g]) {
          used[g] = true;
          s.insert(gs[g].begin(), gs[g].end());
        }
      }
      res.push_back(id);
    }
    if ((int)res.size() == n) {
      reverse(res.begin(), res.end());
      for (int i: res) {
        printf("%d ", i + 1);
      }
      printf("\n");
      return;
    }
  }

  assert(false);
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
