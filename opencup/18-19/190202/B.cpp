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
#define all(a) (a).begin(), (a).end()


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

const int N30 = 30;

//
//vector<double> solve(vector<vector<int>> b) {
////  int n = a.size();
//
//  vector<double> w(N30);
//  vector<int> used(N30);
//  double pool = 1;
//  for (int i = 0; i < N30; i++) {
//    vector<int> cnt(N30);
//    db(i);
//    for (int j = 0; j < (int)b.size(); j++) {
//      for (int k = 0; k < N30; k++) {
//        if (!used[b[j][k]]) {
//          cnt[b[j][k]]++;
//          break;
//        }
//      }
//    }
//    int best = -1;
//    for (int j = 0; j < N30; j++) {
//      if (used[j]) continue;
//      if (best == -1 || cnt[j] >  cnt[best]) best = j;
//    }
//    double part = cnt[best] * 1.0 / (int)b.size();
//    w[best] = part * pool;
//    pool *= (1 - part);
//    used[best] = 1;
//  }
//  return w;
//}

vector<double> solve(vector<vector<int>> b) {
  vector<vector<int>> cnt(N30, vector<int>(N30));
  int m = b.size();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < N30; j++) {
      for (int k = j + 1; k < N30; k++) {
        cnt[b[i][j]][b[i][k]]++;
      }
    }
  }

  vector<vector<int>> e(N30, vector<int>(N30));


  for (int i = 0; i < N30; i++) {
    e[i][i] = 1;
    for (int j = 0; j < N30; j++) {
      if (i == j) continue;
      if (cnt[i][j] != 0 && cnt[i][j] != m) {
        e[i][j] = 1;
        e[j][i] = 1;
      }
    }
  }

  for (int k = 0; k < N30; k++) {
    for (int i = 0; i < N30; i++) {
      for (int j = 0; j < N30; j++) {
        e[i][j] |= e[i][k] && e[k][j];
      }
    }
  }
  vector<double> ans(N30);

  vector<int> used(N30);
  for (int i = 0; i < N30; i++) {
    if (used[i]) continue;
    vector<int> who;
    for (int j = 0; j < N30; j++) {
      if (e[i][j] && e[j][i]) {
        assert(!used[j]);
        used[j] = 1;
        who.push_back(j);
      }
    }
    solve2(cnt, who, ans);
  }


}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  //freopen("b.out", "w", stdout);
#endif

  if (false) {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    vector<vector<int>> b(m, vector<int>(30));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < 30; j++) {
        scanf("%d", &b[i][j]);
      }
    }
//    solve(a, b);
  }
  else {
    for (int tt = 0; tt < 100; tt++) {
      db(tt);
      int n = 30;
//      vector<int> a(n, 1);
      vector<double> w(n);
      double sw = 0;
      for (int i = 0; i < n; i++) {
        w[i] = rand() * 1.0 / RAND_MAX;
        sw += w[i];
      }

      for (int i = 0; i < n; i++) {
        w[i] /= sw;
      }
      int m = 1e5;
      vector<vector<int>> b;
      for (int i = 0; i < m; i++) {
        db(i);
        vector<int> tmp;
        vector<int> used(n, 0);
        for (int j = 0; j < n; j++) {
          vector<pair<double, int>> ord;
          double lw = 0;
          for (int k = 0; k < n; k++) {
            if (!used[k]) {
              ord.push_back({w[k], k});
              lw += w[k];
            }
          }
          for (int k = 0; k < (int)ord.size(); k++) {
            ord[k].first /= lw;
            if (k > 0) {
              ord[k].first += ord[k - 1].first;
            }
          }
          double val = rand() * 1.0 / RAND_MAX;
          int nxt = -1;
          for (int k = 0; k < (int)ord.size(); k++) {
            if (ord[k].first + 1e-9 >= val) {
              nxt = k;
              break;
            }
          }
          assert(nxt != -1);
          tmp.push_back(nxt);
        }
        b.push_back(tmp);
      }
      auto res_w = solve(b);
      double mx_e = 0;
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          double e1 = res_w[i] / (res_w[i] + res_w[j]);
          double e2 = w[i] / (w[i] + w[j]);
          mx_e = max(mx_e, abs(e1 - e2));
        }
      }
      db(mx_e);
      assert(mx_e < 0.02);
    }


  }




  return 0;
}
