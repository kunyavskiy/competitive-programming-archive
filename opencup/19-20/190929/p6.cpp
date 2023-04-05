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

int n, k;
vector<vector<int>> a;
vector<pair<int, int>> ans;

void move(int from, int to) {
  assert(from != to);
  ans.push_back({from, to});
  a[to].push_back(a[from].back());
  a[from].pop_back();
}

void sort(int from, int n, int to, int d) {
  if (n == 0) return;
  if (n == 1) {
    if (from != to) move(from, to);
    return;
  }
  int jj = 0;
  vector<int> q(k);
  for (int i = 0; i < k; i++) {
    if (i == from) continue;
    if (i == to) continue;
    if (jj == k - 2) continue;
    int x = (jj + 1) * n / (k - 2) - jj * n / (k - 2);
    jj++;
    q[i] = x;
    sort(from, x, i, -d);
  }
  for (int i = 0; i < n; i++) {
    int m = -1;
    for (int j = 0; j < k; j++) {
      if (q[j] > 0 && (m == -1 || a[j].back() * d < a[m].back() * d)) {
        m = j;
      }
    }
    assert(m != -1);
    move(m, to);
    q[m]--;
  }
}

int main() {
#ifdef LOCAL
  freopen("p6.in", "r", stdin);
  freopen("p6.out", "w", stdout);
#endif

  scanf("%d%d", &n, &k);
  a.resize(k);
  for (int i = 0; i < k; i++) {
    int x;
    scanf("%d", &x);
    a[i].resize(x);
    for (int j = x - 1; j >= 0; j--) {
        scanf("%d", &a[i][j]);
    }
  }
  for (int i = 0; i < k - 1; i++) {
    while (!a[i].empty()) {
      move(i, k - 1);
    }
  }
  sort(k - 1, n, k - 1, -1);
  for (int i = 0; i < k - 1; i++) {
    int j = i + 1;
    if (j == k - 1) j = i - 1;
    for (int t = 0; t < n / k; t++) {
      move(k - 1, j);
    }
    for (int t = 0; t < n / k; t++) {
      move(j, i);
    }
  }
  assert((int)ans.size() <= 13 * n);
  cout << ans.size() << "\n";
  for (auto p : ans) {
    cout << p.first + 1 << " " << p.second + 1 << "\n";
  }
  return 0;
}
