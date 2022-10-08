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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD)
    a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0)
    a += MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) { return mpow(x, MOD - 2); }

int mex(vector<int> a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  a.push_back(1e9);
  int res = 0;
  while (a[res] == res) res++;
  return res;
}

vector<int> readGraph(int n) {
  vector<vector<int>> g(n);
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    if (a < b) {
      g[a].push_back(b);
    } else {
      g[b].push_back(a);
    }
  }

  vector<int> id(n);
  for (int i = n - 1; i >= 0; i--) {
    vector<int> nxt;
    nxt.reserve(g[i].size());
    for (int v : g[i]) {
      nxt.push_back(id[v]);
    }
    id[i] = mex(nxt);
  }

  vector<int> score(*max_element(id.begin(), id.end()) + 1);
  int v = ll(1e18) % MOD;
  int cur = v;
  for (int i = 0; i < n; i++) {
    add(score[id[i]], cur);
    cur = mul(cur, v);
  }
  return score;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> g1 = readGraph(n);
    vector<int> g2 = readGraph(n);
    vector<int> g3 = readGraph(n);

    auto get = [](const vector<int>&a, int pos) {
      if (pos < (int)a.size()) return a[pos];
      return 0;
    };

    int ans = 0;
    for (int i = 0; i < (int)g1.size(); i++) {
      for (int j = 0; j < (int)g2.size(); j++) {
        int cur = mul(g1[i], g2[j]);
        cur = mul(cur, get(g3, i ^ j));
        add(ans, cur);
      }
    }
    printf("%d\n", ans);
  }


  return 0;
}
