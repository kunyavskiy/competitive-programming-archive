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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
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
  freopen("bb.in", "r", stdin);
  freopen("bb.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  static char s[1001];

  vector<vector<int>> a(n, vector<int>(m));
  vector<vector<int>> b(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    scanf("%s", s);
    for (int j = 0; j < m; j++) {
      a[i][j] = s[j] == 'O';
    }
  }
  for (int i = 0; i < n; i++) {
    scanf("%s", s);
    for (int j = 0; j < m; j++) {
      b[i][j] = s[j] == 'O';
    }
  }

  vector<int> cr(n);
  vector<int> cc(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (b[i][j] == 0) {
        cr[i]++;
        cc[j]++;
      }
    }
  }

  bool ok = false;
  vector<bool> gr(n);
  vector<bool> gc(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (b[i][j] == 0 && cr[i] == 1 && cc[j] == 1) {
        ok = true;
        gr[i] = true;
        gc[j] = true;
      }
    }
  }

  if (ok) {
    for (int i = 0; i < n; i++) {
      if (cr[i] == 0) gr[i] = true;
    }
    for (int j = 0; j < m; j++) {
      if (cc[j] == 0) gc[j] = true;
    }
  }

  ok = false;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (gr[i] && gc[j] && a[i][j] == 1) ok = true;
    }
  }

  if (!ok) {
    ok = true;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (a[i][j] != b[i][j]) ok = false;
      }
    }
  } else {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (!gr[i] && !gc[j] && (a[i][j] != b[i][j]))
          ok = false;
      }
    }
  }
  cout << ok << endl;

  return 0;
}
