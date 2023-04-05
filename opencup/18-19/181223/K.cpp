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
  freopen("k.in", "r", stdin);
  //freopen("k.out", "w", stdout);
#endif

  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    a[i]--;
  }

  vector<vector<pair<int, int>>> seg(m, vector<pair<int, int>>(1, {n, n}));
  vector<int> cur_r(m, n);

  for (int i = n - 1; i >= 0; i--) {
    int x = a[i];
//    cerr << x << endl;
    int r = i;
    while (x < m && r < cur_r[x]) {
//      cerr << x << " " << r << "\n";
      seg[x].push_back({i, r});
      cur_r[x] = r;
      int L = 0;
      int R = (int)seg[x].size();
//      cerr << x << " " << r << " " << L << " " << R << endl;
      while (R > L + 1) {
        int M = (L + R) / 2;
        if (seg[x][M].first > r) {
          L = M;
        } else {
          R = M;
        }
      }
      assert(L < (int)seg[x].size());
      r = seg[x][L].second;
      x++;

    }
  }

  vector<vector<ll>> ps(m);
  for (int i = 0; i < m; i++) {
    ps[i].resize(seg[i].size() + 1);
    for (int j = 0; j < (int)seg[i].size(); j++) {
        ll ll = j + 1 < (int)seg[i].size() ? seg[i][j + 1].first : -1;
        ps[i][j + 1] = ps[i][j] + seg[i][j].second * (seg[i][j].first - ll);
    }
  }

//  for (auto p : seg[1]) {
//    cerr << p.first << ": " << p.second << "\n";
//  }

  for (int i = 0; i < q; i++) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    l--;
    r--;
    k--;
    int L = 0;
    int R = seg[k].size();
    while (R > L + 1) {
      int M = (L + R) / 2;
      if (seg[k][M].first >= l) {
        L = M;
      } else {
        R = M;
      }
    }
    int LL = L - 1;
    L = 0;
    R = seg[k].size();
    while (R > L + 1) {
      int M = (L + R) / 2;
      if (seg[k][M].second > r) {
        L = M;
      } else {
        R = M;
      }
    }
    int RR = R;

//    cout << LL << " " << RR << "\n";

    if (LL + 1 < RR) {
      cout << "0\n";
    } else {
      ll res = ps[k][LL + 1] - ps[k][RR];
//      cerr << res << "\n";
      res += seg[k][LL + 1].second * (seg[k][LL + 1].first - l + 1LL);
//      cerr << res << "\n";
      res = (seg[k][RR].first - l + 1LL) * (r + 1) - res;
      cout << res << "\n";
    }
  }

  return 0;
}
