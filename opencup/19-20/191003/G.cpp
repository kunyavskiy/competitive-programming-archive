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

int solve(int x) {
  static map<int, int> mp;
  if (mp.count(x)) {
    return mp[x];
  }
  int res;

  vector<int> vct;
  for (int i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      vct.push_back(i);
      if (i * i != x) {
        vct.push_back(x / i);
      }
    }
  }
  sort(vct.begin(), vct.end());

  int n = vct.size();
  vector<vector<int>> e(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (vct[i] % vct[j] == 0) {
        e[i].push_back(j);
      }
    }
  }

  vector<int> vis(n);
  int tmr;
  vector<int> mt(n, -1), tm(n, -1);
  function<bool(int)> dfs = [&](int v) {
    if (vis[v] == tmr) return false;
    vis[v] = tmr;
    for (int to : e[v]) {
      if (mt[to] == -1 || dfs(mt[to])) {
        mt[to] = v;
        tm[v] = to;
        return true;
      }
    }
    return false;
  };
  for (int run = 1; run;) {
    tmr++;
    run = 0;
    for (int i = 0; i < n; i++) {
      if (tm[i] == -1) {
        if (dfs(i)) {
          run = 1;
        }
      }
    }
  }
  int cnt = 0;
  for (int i = 0; i < n; i++) cnt += mt[i] != -1;
  res = n - cnt;

  mp[x] = res;
  return res;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    cout << solve(n) << endl;
  }

  return 0;
}
