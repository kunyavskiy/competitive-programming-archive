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

const int INF = 1e9;

void solve(int m) {
  int N = 500;
  vector<int> dp(N + 1, INF);
  dp[0] = dp[1] = 0;
  vector<vector<int>> pr(N + 1);


  for (int n = 2; n <= N; n++) {
    for (int frst = 0; frst <= n; frst++) {
      for (int last = 0; frst + last < n; last++) {
        for (int cnt = 1; cnt <= 6; cnt++) {
          if (frst + last + 1 + cnt <= n) {
            int k = n - frst - last - 1 - cnt;

            int cost = 0;
            cost += frst + dp[frst];
            cost += last + dp[last];
            cost += cnt * (cnt + 1) / 2;
            for (int i = 0; i < cnt; i++) {
              int cur = k / cnt + (i < k % cnt);
              cost += dp[cur] + cur * 2;
            }
            if (dp[n] > cost) {
              dp[n] = cost;
              pr[n].clear();
              pr[n].push_back(frst);
              for (int i = 0; i < cnt; i++) pr[n].push_back(k / cnt + (i < k % cnt));
              pr[n].push_back(last);
            }
            dp[n] = min(dp[n], cost);
          }
        }
      }
    }

    if (dp[n] > 5 * n) {
      cout << "FAIL" << endl;
      exit(0);
    }
  }


  vector<pair<int, int>> ans;
  function<void(int, int)> rec = [&](int start, int n) {
    if (n <= 1) return;
//    db2(start, n);
    vector<int> vct = pr[n];
    vector<int> mid;

    int cur = start - 1;
    mid.push_back(cur);
    for (int x : vct) {
      cur += x + 1;
      mid.push_back(cur);
    }
//    dbv(mid);
    for (int i = 0; i < (int)mid.size(); i++) {
      for (int j = i + 1; j < (int)mid.size(); j++) {
        if (i == 0) continue;
        if (j + 1 == (int)mid.size()) continue;
        ans.push_back({mid[i], mid[j]});
      }
    }
    for (int i = 1; i + 1 < (int)mid.size(); i++) {
      for (int j = mid[i - 1] + 1; j < mid[i + 1]; j++) {
        if (j == mid[i]) continue;
        ans.push_back({j, mid[i]});
      }
    }
    for (int i = 0; i + 1 < (int)mid.size(); i++) {
      rec(mid[i] + 1, mid[i + 1] - mid[i] - 1);
    }
  };
  rec(1, m);
  for (auto &o : ans) if (o.first > o.second) swap(o.first, o.second);
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

  assert((int)ans.size() <= 5 * m);
  cout << ans.size() << endl;
  for (auto o : ans) {
    cout << o.first << " " << o.second << endl;
  }
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif

  int m;
  while (cin >> m) {
    solve(m);
  }

  return 0;
}
