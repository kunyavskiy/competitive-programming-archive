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

struct segment {
  int l, r, c;
};

void solve_test() {
  int n;
  cin >> n;
  vector<segment> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i].l >> s[i].r >> s[i].c;
    s[i].r++;
  }
  vector<int> ts;
  for (int i = 0; i < n; i++) {
    ts.push_back(s[i].l);
    ts.push_back(s[i].r);
  }
  sort(ts.begin(), ts.end());
  ts.erase(unique(ts.begin(), ts.end()), ts.end());
  for (int i = 0; i < n; i++) {
    s[i].l = lower_bound(ts.begin(), ts.end(), s[i].l) - ts.begin();
    s[i].r = lower_bound(ts.begin(), ts.end(), s[i].r) - ts.begin();
  }
  sort(s.begin(), s.end(), [](const segment &a, const segment &b){
    if (a.r != b.r)
      return a.r < b.r;
    else
      return a.l < b.l;
  });

  int MAX = 201;
  vector<vector<char>> can(n, vector<char>(MAX));
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < MAX; c++) {
      if (s[i].c == c || s[i].c == 0) {
        can[i][c] = true;
        for (int j = 0; j < n; j++) {
          if (s[j].c != 0 && s[j].c != c) {
            if (max(s[i].l, s[j].l) < min(s[i].r, s[j].r)) {
              can[i][c] = false;
            }
          }
        }
      }
    }
  }

//  for (auto &ss : s) {
//    db3(ss.l, ss.r, ss.c);
//
//  }

  vector<int> nx(n);
  for (int i = 0; i < n; i++) {
    int mx = i;
    for (int j = 0; j < n; j++) {
      if (max(s[i].l, s[j].l) < min(s[i].r, s[j].r)) {
        if (s[j].r > s[mx].r) mx = j;
      }
    }
    nx[i] = mx;
  }


  vector<int> dp2(ts.size() + 1);

  vector<vector<int>> dp(n, vector<int>(MAX, -1));
  vector<vector<int>> ndp(n, vector<int>(MAX, -1));
  int res = 0;
  for (int i = 0; i < n; i++) {
    int dd = 0;
    for (int j = 0; j <= s[i].l; j++) {
      dd = max(dd, dp2[j]);
    }
    for (int j = 0; j < n; j++) {
      for (int c = 0; c < MAX; c++) {
        ndp[j][c] = -1;
      }
    }
    for (int c = 0; c < MAX; c++) {
      if (!can[i][c]) continue;
      int mx = nx[i];
      dp[mx][c] = max(dp[mx][c], dd + 1);

      for (int j = 0; j < n; j++) {
        if (dp[j][c] == -1) continue;
        if (i < n - 1 && s[i + 1].l < s[j].r) {
          ndp[j][c] = max(ndp[j][c], dp[j][c]);
          int jj;
          if (s[nx[i + 1]].r > s[j].r) {
            jj = nx[i + 1];
          } else {
            jj = j;
          }
//          int jj = max(j, nx[i + 1]);
          ndp[jj][c] = max(ndp[jj][c], dp[j][c] + 1);
        }
//        cout << i << " " << j << " " << c << " " << dp[j][c] << "\n";
        res = max(res, dp[j][c]);
        dp2[s[j].r] = max(dp2[s[j].r], dp[j][c]);
      }

    }
    swap(dp, ndp);
  }
  cout << res << "\n";
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) solve_test();

  return 0;
}
