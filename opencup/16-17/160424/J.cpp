//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "J"

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

const int MAXN = 20000;
const int MAXT = 10;

int cost[MAXN][MAXT];
int n, m, t;

int day[MAXN];

set<pair<int, int>> g[MAXT + 2][MAXT + 2];

void remove_person(int v) {
  if (day[v] == -1) {
    for (int i = 0; i < t; i++) {
      if (v < n) {
        g[t][i].erase(make_pair(-cost[v][i], v));
      } else {
        g[i][t+1].erase(make_pair(-cost[v][i], v));
      }
    }
  } else {
    int d = day[v];
    for (int i = 0; i < t; i++) {
      if (i != d) {
        if (v < n) {
          g[d][i].erase(make_pair(cost[v][d] - cost[v][i], v));
        } else {
          g[i][d].erase(make_pair(cost[v][d] - cost[v][i], v));
        }
      }
    }
  }
}

void add_person(int v) {
  if (day[v] == -1) {
    for (int i = 0; i < t; i++) {
      if (v < n) {
        g[t][i].insert(make_pair(-cost[v][i], v));
      } else {
        g[i][t+1].insert(make_pair(-cost[v][i], v));
      }
    }
  } else {
    int d = day[v];
    for (int i = 0; i < t; i++) {
      if (v < n) {
        g[d][i].insert(make_pair(cost[v][d] - cost[v][i], v));
      } else {
        g[i][d].insert(make_pair(cost[v][d] - cost[v][i], v));
      }
    }
  }
}

const int INF = (int) 1.1e9;

int get_path(vector<pair<int, int>>& path) {
  vector<int> d(t + 2, INF);
  vector<int> p(t + 2, -1);
  d[t] = 0;

  for (int i = 0; i < t + 2; i++) {
    for (int j = 0; j < t + 2; j++) {
      for (int k = 0; k < t + 2; k++) {
        if (g[j][k].empty()) continue;
        if (d[k] > d[j] + g[j][k].begin()->first) {
          assert(k != t);
          d[k] = d[j] + g[j][k].begin()->first;
          p[k] = j;
        }
      }
    }
  }

  if (d[t+1] >= 0) return d[t+1];

  vector<pair<int, int>> v;
  path.clear();
  int cur = t + 1;
  while (cur != t) {
    int par = p[cur];
    assert(!g[par][cur].empty());
    int id = g[par][cur].begin()->second;
    path.push_back(make_pair(cur, id));
    cur = par;
  }
  reverse(path.begin(), path.end());
  return d[t+1];
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  scanf("%d%d%d",&n,&m,&t);

  memset(day, -1, sizeof(day));

  for (int i = 0; i < n + m; i++) {
    for (int j = 0; j < t; j++) {
      scanf("%d",&cost[i][j]);
    }
  }

  for (int i = 0; i < n + m; i++) {
    add_person(i);
  }

  int ans = 0;

  while (true) {
    vector<pair<int, int>> path;
    int cost = get_path(path);
    if (cost < 0) {
      ans += cost;
    } else {
      break;
    }

    for (int i = 0; i < (int)path.size(); i++) {
      remove_person(path[i].second);
      if (path[i].second < n) {
        assert(path[i].first < t);
        day[path[i].second] = path[i].first;
      } else {
        assert(i);
        assert(path[i - 1].first < t);
        day[path[i].second] = path[i - 1].first;
      }
    }

    for (int i = 0; i < (int)path.size(); i++) {
      add_person(path[i].second);
    }
  }

  printf("%d\n", -ans);
  return 0;
}
