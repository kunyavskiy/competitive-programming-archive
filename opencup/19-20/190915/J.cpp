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

struct Sum {
  int n, m;
  vector<vector<int>> s;

  Sum(vector<vector<int>> a) {
    n = a.size();
    m = a[0].size();
    s.resize(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i - 1][j - 1];
      }
    }
  }

  int get(int lx, int ly, int rx, int ry) {
    return s[rx + 1][ry + 1] - s[lx][ry + 1] - s[rx + 1][ly] + s[lx][ly];
  }
};

bool solve(vector<string> a) {
  int n = a.size();
  int m = a[0].size();

  vector<vector<int>> good_start(n, vector<int>(m));
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < m - 1; j++) {
      good_start[i][j] = a[i + 1][j] == a[i][j + 1];
    }
  }
  Sum s(good_start);

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < m - 1; j++) {
      if (good_start[i][j] && s.get(i + 1, j + 1, n - 1, m - 1)) {
        return true;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i + 2 < n && j + 1 < m) {
        if (good_start[i][j] && good_start[i + 1][j]) {
          return true;
        }
      }
      if (i + 1 < n && j + 2 < m) {
        if (good_start[i][j] && good_start[i][j + 1]) {
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
//  freopen("j.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
      static char buf[(int)1e4];
      scanf(" %s", buf);
      a[i] = buf;
    }

    cout << (solve(a) ? "YES" : "NO") << endl;
  }

  return 0;
}
