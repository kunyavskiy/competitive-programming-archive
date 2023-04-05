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
  freopen("p10.in", "r", stdin);
  freopen("p10.out", "w", stdout);
#endif

  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<string> all;
  vector<vector<string>> names(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    names[i].resize(x);
    for (int j = 0; j < x; j++) {
      cin >> names[i][j];
      all.push_back(names[i][j]);
    }
  }
  map<string, int> id;
  sort(all.begin(), all.end());
  for (int i = 0; i < (int)all.size(); i++) {
    id[all[i]] = i;
  }
  vector<vector<int>> a(n);
  for (int i = 0; i < n; i++) {
    for (string s : names[i]) {
      a[i].push_back(id[s]);
    }
    sort(a[i].begin(), a[i].end());
  }

  vector<bool> z(n);
  vector<int> p(n);
  int last = -1;
  for (int i = 0; i < n; i++) {
    int besti = -1;
    int best = -1;
    for (int j = 0; j < n; j++) {
      if (z[j]) continue;
      int x = lower_bound(a[j].begin(), a[j].end(), last) - a[j].begin();
      if (x == (int)a[j].size()) {
        p[i] = j;
        z[j] = true;
        for (int k = 0; k < n; k++) {
          if (z[k]) continue;
          p[++i] = k;
        }
        cerr << "1";
        cout << "NO\n";
        for (int k = 0; k < n; k++) {
          cout << p[k] + 1 << " ";
        }
        return 0;
      } else {
        if (a[j][x] > best) {
          best = a[j][x];
          besti = j;
        }
      }
    }
    z[besti] = true;
    p[i] = besti;
    last = best;
  }

  vector<int> dp(1 << n, 0);
  vector<int> pr(1 << n, 0);
  for (int x = 0; x < (1 << n); x++) {
    for (int i = 0; i < n; i++) {
      if (x & (1 << i)) continue;
      int j = lower_bound(a[i].begin(), a[i].end(), dp[x]) - a[i].begin();
      if (j == (int)a[i].size()) {
        vector<int> ans;
        for (int t = 0; t < n; t++) {
          if (!(x & (1 << t))) {
            db(t);
            ans.push_back(t);
          }
        }
        cerr << x << "\n";
        while (x > 0) {
          int t = __builtin_ctz(x ^ pr[x]);
          db3(x,pr[x],t);
          ans.push_back(t);
          x = pr[x];
        }
        reverse(ans.begin(), ans.end());
        cout << "NO\n";
        for (int k = 0; k < n; k++) {
          cout << ans[k] + 1 << " ";
        }
        return 0;
      } else {
        int xx = x | (1 << i);
        if (dp[xx] < a[i][j]) {
          dp[xx] = a[i][j];
          pr[xx] = x;
        }
      }
    }
  }
  cout << "YES";


  return 0;
}
