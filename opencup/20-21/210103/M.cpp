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

struct Edge {
  int from;
  int to;
  int min;
  int max;
  bool isBST;

  Edge(int from, int to) {
    this->from = from;
    this->to = to;
    min = max = -1;
    isBST = false;
  }
};


vector<vector<Edge>> tree;

bool calc(Edge& e) {
  if (e.min != -1) {
    return e.isBST;
  }
  e.min = e.max = e.to;
  e.isBST = true;
  int countLess = 0, countMore = 0;
  for (Edge &next : tree[e.to]) {
    if (next.to == e.from) {
      continue;
    }
    e.isBST &= calc(next);
    if (next.max < e.to) {
      countLess++;
      e.min = next.min;
    } else if (next.min > e.to) {
      countMore++;
      e.max = next.max;
    } else {
      e.isBST = false;
    }
  }
  e.isBST &= countLess <= 1 && countMore <= 1;
  return e.isBST;
}

void solve(int n) {
  tree = vector<vector<Edge>>(n);
  for (int i = 0; i < n - 1; i++) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from, --to;
    tree[from].push_back(Edge(from, to));
    tree[to].push_back(Edge(to, from));
  }
  for (int i = 0; i < n; i++) {
    if (tree[i].size() > 3) {
      printf("-1\n");
      return;
    }
  }
  vector<int> result;
  for (int i = 0; i < n; i++) {
    if (tree[i].size() > 2) {
      continue;
    }
    bool ok = true;
    int countLess = 0, countMore = 0;
    for (Edge& e : tree[i]) {
      ok &= calc(e);
      if (e.max < i) {
        countLess++;
      } else if (e.min > i) {
        countMore++;
      } else {
        ok = false;
      }
    }
    ok &= countLess <= 1 && countMore <= 1;
    if (ok) {
      result.push_back(i + 1);
    }
  }
  if (result.empty()) {
    printf("-1\n");
  } else {
    for (int i : result) {
      printf("%d ", i);
    }
    printf("\n");
  }
}


int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    solve(n);
  }

  return 0;
}
