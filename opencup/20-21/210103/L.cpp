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

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    eprintf("%d %d\n", n, k);
    vector<int> cnt(k, 0);
    vector<int> a(n);
    vector<vector<int>> v;
    vector<vector<int>> poss(k);
    vector<int> prev(n, -1);
    vector<int> next(n, -1);
    vector<bool> in_seq(n);
    v.emplace_back();
    for (int i = 0; i < n; i++) {
      int &x = a[i];
      scanf("%d", &x);
      --x;
      poss[x].push_back(i);
      if ((int)v[cnt[x]].size() == x) {
        v[cnt[x]].push_back(i);
        if (!v.back().empty()) {
          v.emplace_back();
        }
        cnt[x]++;
      }
    }
    v.erase(v.begin() + cnt.back(), v.end());
    for (const auto& x : v) {
      for (int i = 0; i < (int) x.size(); i++) {
        in_seq[x[i]] = true;
        if (i) {
          prev[x[i]] = x[i - 1];
          next[x[i - 1]] = x[i];
        }
      }
    }
    vector<bool> used[2];
    used[0].resize(n);
    used[1].resize(n);
    queue<pair<int, int>> q;
    auto visit = [&](int v, int side) {
      if (!used[side][v]) {
        q.emplace(v, side);
        used[side][v] = true;
      }
    };
    for (int i : poss[0]) {
      visit(i, 0);
    }
    while (!q.empty()) {
      auto [v, side] = q.front();
      q.pop();
      if (side == 0) {
        if (!in_seq[v]) {
          visit(v, 1);
        } else if (prev[v] != -1) {
          visit(prev[v], 1);
        }
      } else {
        int val = a[v];
        assert(val != k - 1);
        if (in_seq[v]) {
          visit(v, 0);
        }
        vector<int> &vec = poss[val + 1];
        while (!vec.empty() && vec.back() >= v) {
          int x = vec.back();
          vec.pop_back();
          visit(x, 0);
        }
      }
    }

    vector<int> ans;
    for (int i = 0; i < n; i++) {
      if (used[0][i] && !used[1][i]) {
        ans.push_back(i);
      }
    }
    assert((int)ans.size() == cnt.back());
    printf("%d\n", (int)ans.size());
    for (int x : ans) {
      printf("%d ", x + 1);
    }
    printf("\n");
  }

  return 0;
}
