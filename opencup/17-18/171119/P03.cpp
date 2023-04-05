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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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
typedef pair<int,int> pii;

const ll INF = (1LL << 60);

const int MAXN = 2001;
const int MAXT = 4 * (2 * 2 * 3 * 5 * 7);
pii p[MAXN];

int n, m, k, s;
int aa[MAXN];
int tt[MAXN];
int pp[MAXN];

int neigh[4][MAXN];
ll dist[4][MAXT][MAXN];

const int reflect[4][4] = {
    {2, 1, 0, 3},
    {3, 2, 1, 0},
    {0, 3, 2, 1},
    {1, 0, 3, 2},
};

static inline int findDir(int dir, int i, int t) {
  if (i < k + 1) {
    return dir;
  }
  int numMir = i - k - 1;
  int curA;
  if (tt[numMir] == -1) {
    curA = aa[numMir];
  } else {
    curA = (aa[numMir] + (t - tt[numMir] + MAXT) / pp[numMir] + 1) % 4;
  }
  eprintf("dir %d curA %d => %d\n", dir, curA, reflect[dir][curA]);
  return reflect[curA][dir];
}

int distTwoPoint(int i, int j) {
  return abs(p[i].first - p[j].first) + abs(p[i].second - p[j].second);
}

int distToBorder(int i, int dir) {
  if (dir == 0) {
    return m - p[i].first + 1;
  } else if (dir == 1) {
    return n - p[i].second + 1;
  } else if (dir == 2) {
    return p[i].first;
  } else if (dir == 3) {
    return p[i].second;
  } else {
    assert(0);
  }
}

ll findDist(int i, int dir, int t) {
  auto &curD = dist[dir][t][i];
  if (i == 0) {
    return curD = 0;
  }
  if (curD == -1) {
    curD = INF;
    int newI = neigh[dir][i];
    int delta, newDir, newT;
    if (newI == -1) {
      newI = i;
      delta = distToBorder(i, dir) * 2 - 1;
      newT = (t + delta) % MAXT;
      newDir = findDir(dir ^ 2, newI, newT);
    } else {
      delta = distTwoPoint(i, newI);
      newT = (t + delta) % MAXT;
      newDir = findDir(dir, newI, newT);
    }
    curD = findDist(newI, newDir, newT);
    if (curD != INF) {
      curD += delta;
    }
  }
  return curD;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int x0, y0;
  scanf("%d%d%d%d%d%d", &n, &m, &k, &s, &y0, &x0);
  p[0] = pii(x0, y0);
  for (int i = 0; i < k; ++i) {
    int x, y;
    scanf("%d%d", &y, &x);
    p[i + 1] = pii(x, y);
  }
  for (int i = 0; i < s; ++i) {
    int x, y, a, t, per;
    scanf("%d%d%d%d%d", &y, &x, &a, &t, &per);
    p[i + 1 + k] = pii(x, y);
    if (t == -1) {
      aa[i] = a;
      tt[i] = t;
      pp[i] = per;
    } else {
      if (t == per) {
        t = 0;
        a = (a + 3) % 4;
      }
      aa[i] = a;
      tt[i] = t;
      pp[i] = per;
    }
  }

  map<int, vector<pii>> rows, cols;
  int N = k + s + 1;
  for (int i = 0; i < N; ++i) {
    rows[p[i].first].push_back(pii(p[i].second, i));
    cols[p[i].second].push_back(pii(p[i].first, i));
  }

  memset(neigh, 0xff, sizeof(neigh));
  for (auto it : rows) {
//    int x = it.first;
    auto & yy = it.second;
    sort(yy.begin(), yy.end());
    for (int i = 1; i < int(yy.size()); ++i) {
      int u = yy[i - 1].second;
      int v = yy[i].second;
      neigh[1][u] = v;
      neigh[3][v] = u;
    }
  }
  for (auto it : cols) {
//    int y = it.first;
    auto & xx = it.second;
    sort(xx.begin(), xx.end());
    for (int i = 1; i < int(xx.size()); ++i) {
      int u = xx[i - 1].second;
      int v = xx[i].second;
      neigh[0][u] = v;
      neigh[2][v] = u;
    }
  }

  memset(dist, 0xff, sizeof(dist));
  ll ans = INF;
  for (int i = 1; i < k + 1; ++i) {
    for (int dir = 0; dir < 4; ++dir) {
      for (int t = 0; t < MAXT; ++t) {
        ans = min(ans, findDist(i, dir, t) + t);
      }
    }
  }
  if (ans == INF) {
    printf("-1\n");
  } else {
    printf("%lld\n", ans);
  }

  return 0;
}

