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


const int MAXN = 2100;

vector<int> g[MAXN];
int to[MAXN];
int inv_cur[MAXN];
int cur[MAXN];
int size[MAXN];
int p[MAXN];

vector<int> ans;

void dfs_sizes(int v) {
  size[v] = 1;
  for (int u : g[v]) {
    dfs_sizes(u);
    size[v] += size[u];
  }
}

void do_swap(int a, int b) {
  swap(cur[a], cur[b]);
  inv_cur[cur[a]] = a;
  inv_cur[cur[b]] = b;
}

void do_rotate(int v) {
  while (v != 0) {
    do_swap(v, p[v]);
    v = p[v];
  }
}

int remove_vertex(int v) {
  while (v != -1) {
    --size[v];
    v = p[v];
  }
}

int get_small() {
  int v = 0;
  while (size[v] > 1) {
    int minu = -1;
    for (int u : g[v]) {
      if (size[u] > 0 && (minu == -1 || size[u] < size[minu])) {
        minu = u;
      }
    }
    assert(minu != -1);
    v = minu;
  }
  return v;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  p[0] = -1;
  for (int i = 1; i < n; i++) {
    scanf("%d", &p[i]);
    g[p[i]].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    to[x] = i;
    cur[i] = i;
    inv_cur[i] = i;
  }

  dfs_sizes(0);

  reverse(ans.begin(), ans.end());
  printf("%d\n", (int)ans.size());
  for (int x : ans) {
    printf("%d ", x);
  }
  printf("\n");
  return 0;
}
