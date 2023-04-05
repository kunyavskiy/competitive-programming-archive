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

const int MAXN = 300000;
int a[MAXN];
int b[MAXN];
int w[MAXN];
int na[MAXN];
int nb[MAXN];
set<int> to_merge;
set<pair<int, int>> to_trigger[MAXN];

int p[MAXN];
ll sz[MAXN];

int get(int x) {
  if (x == p[x]) return x;
  return p[x] = get(p[x]);
}

bool join(int a, int b) {
  a = get(a);
  b = get(b);
  if (a == b) return false;
  if (to_trigger[a].size() <= to_trigger[b].size()) {
    swap(a, b);
  }
  to_trigger[a].insert(to_trigger[b].begin(), to_trigger[b].end());
  to_trigger[b].clear();
  p[b] = a;
  sz[a] += sz[b];
  return true;
}

void schedule(int id) {
  int aa = get(a[id]);
  int bb = get(b[id]);
  if (aa == bb) {
    return;
  }
  if (sz[aa] + sz[bb] >= w[id]) {
    to_merge.insert(id);
  } else {
    int need_more = w[id] - sz[aa] - sz[bb];
    to_trigger[aa].emplace(na[id] = sz[aa] + (need_more + 1) / 2, id);
    to_trigger[bb].emplace(nb[id] = sz[bb] + (need_more + 1) / 2, id);
  }
}

void poll(int v) {
  v = get(v);
  while (!to_trigger[v].empty() && to_trigger[v].begin()->first <= sz[v]) {
    int id = to_trigger[v].begin()->second;
    int aa = get(a[id]);
    int bb = get(b[id]);
    to_trigger[aa].erase({na[id], id});
    to_trigger[bb].erase({nb[id], id});
    schedule(id);
  }
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < n; i++) {
      scanf("%lld", &sz[i]);
      p[i] = i;
      to_trigger[i].clear();
    }
    for (int i = 0; i < m; i++) {
      scanf("%d%d%d", &a[i], &b[i], &w[i]);
      --a[i], --b[i];
      schedule(i);
    }

    vector<int> answer;
    while (!to_merge.empty()) {
      int id = *to_merge.begin();
      to_merge.erase(to_merge.begin());
      if (join(a[id], b[id])) {
        answer.push_back(id);
        poll(a[id]);
      }
    }

    printf("%d\n", (int)answer.size());
    for (int x : answer) {
      printf("%d ", x + 1);
    }
    printf("\n");

  }


  return 0;
}
