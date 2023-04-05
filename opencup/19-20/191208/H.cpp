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

char buf[111];

vector<int> p(4);

void join(int x, int y) {
  int k = p[x];
  for (int i = 0; i < 4; i++) {
    if (p[i] == k) p[i] = p[y];
  }
}


void solve_test() {
  int n;
  scanf("%d", &n);
  vector<string> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    a[i] = buf;
  }

  for (int i = 0; i < 4; i++) {
    p[i] = i;
  }
  vector<int> d_in(4);
  vector<int> d_out(4);

  int c_a = 0;

  int res0 = 0;
  for (int i = 0; i < n; i++) {
    int s = 0;
    int t = 1;
    if (a[i] == "A") {
      c_a++;
      continue;
    }
    if (a[i].size() >= 2 && a[i].substr(a[i].size() - 2, 2) == "SA") t = 2;
    if (a[i].size() >= 2 && a[i].substr(0, 2) == "AD") s = 3;
    if (a[i].size() >= 1 && a[i].substr(a[i].size() - 1, 1) == "S") t = 3;
    if (a[i].size() >= 1 && a[i].substr(0, 1) == "D") s = 2;
    for (int j = 0; j < (int) a[i].size() - 2; j++) {
      if (a[i].substr(j, 3) == "SAD") res0++;
    }
    join(s, t);
    d_out[s]++;
    d_in[t]++;
  }

  int res = res0;
  for (int i = 0; i <= c_a; i++) {
    int s = -i;
    for (int j = 0; j < 4; j++) {
      int e = 0;
      int t = 0;
      for (int k = 0; k < 4; k++) {
        if (p[k] != j) continue;
        e += d_out[k];
        if (d_out[k] > d_in[k]) {
          t += d_out[k] - d_in[k];
        }
      }
      if (e == 0) continue;
      s += e - max(t, 1);
    }
    res = max(res, res0 + s);
    join(2, 3);
    d_out[3]++;
    d_in[2]++;
  }
  cout << res << "\n";
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    cout << "Case #" << (i + 1) << ": ";
    solve_test();
  }

  return 0;
}
