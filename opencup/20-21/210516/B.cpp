#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time : %.3lf s.\n", (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

vector<int> build(string s) {
  int n = s.size();
  vector<int> res(n + 1);
  for (int i = 0; i < n; i++) {
    if (s[i] == '+') {
      res[i + 1] = max(res[i + 1], res[i] + 1);
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == '-') {
      res[i] = max(res[i], res[i + 1] + 1);
    }
  }
  return res;
}
int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif
  int n;
  cin >> n;
  string s;
  cin >> s;
  bool x = false;
  string a, b;
  for (int i = 2; i < n; i += 2) {
    string c = s.substr(i, 2);
    if (c == "LL") {
      x = true;
    } else {
      string &ss = x ? b : a;
      if (c == "RL") ss += '-';
      else
        ss += '+';
    }
  }
  reverse(b.begin(), b.end());
  for (char &c : b) {
    if (c == '-') c = '+';
    else
      c = '-';
  }
  vector<int> aa = build(a);
  vector<int> bb = build(b);
  int mn = aa[0] + bb[0] + 1;
  mn = max(mn, aa.back() + bb.back() + 1);
  for (int xx : aa) mn = max(mn, xx + 1);
  for (int xx : bb) mn = max(mn, xx + 1);
  const int INF = 1000000000;
  int res = INF;
  for (int h = mn; h <= 800; h++) {
    int na = aa.size();
    int nb = bb.size();
    vector<vector<int>> d(na + 1, vector<int>(nb + 1, INF));
    d[0][0] = 0;
    for (int i = 1; i <= na; i++) {
      for (int j = 1; j <= nb; j++) {
        d[i][j] = INF;
        if (aa[i - 1] + bb[j - 1] < h) {
          if (i == 1 || j == 1 || (aa[i - 2] + bb[j - 1] < h && aa[i - 1] + bb[j - 2] < h)) {
            d[i][j] = min(d[i][j], d[i - 1][j - 1] + 1);
          }
          d[i][j] = min(d[i][j], d[i - 1][j] + 1);
          d[i][j] = min(d[i][j], d[i][j - 1] + 1);
        }
      }
    }
    if (d[na][nb] < INF) {
      res = min(res, h * d[na][nb]);
    }
  }
  cout << res << "\n";

  return 0;
}
