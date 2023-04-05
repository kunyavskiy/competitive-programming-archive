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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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


const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int my_pow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

const int MAXN = 350;

vector<int> a[MAXN];

int n, m, k;
int ans;

void go(int col, int l, int r, const vector<int>& need) {
  if (col == m) {
    add(ans, my_pow(k, r - l));
    return;
  }
  int cnt = 0;
  bool need_done = false;

  for (int i = l; i < r; ) {
    int j = i;
    while (j < r && a[i][col] == a[j][col]) {
      j++;
    }
    cnt++;
    if (need[col] == a[i][col] || need[col] == -1) {
      need_done = true;
      vector<int> need2 = need;
      need2[col] = a[i][col];
      bool fail = false;
      for (int k = l; k < r && !fail; k++) {
        if (i <= k && k < j) continue;
        for (int t = 0; t < m && !fail; t++) {
          if (a[k][col] != a[k][t]) {
            if (need2[t] == -1 || need2[t] == a[k][t]) {
              need2[t] = a[k][t];
            } else {
              fail = 1;
            }
          }
        }
      }
      if (!fail) {
        go(col + 1, i, j, need2);
      }
    }
    i = j;
  }
  if (need[col] != -1 && need_done) return;
  vector<int> need2 = need;
  bool fail = false;
  for (int k = l; k < r && !fail; k++) {
    for (int t = 0; t < m && !fail; t++) {
      if (a[k][col] != a[k][t]) {
        if (need2[t] == -1 || need2[t] == a[k][t]) {
          need2[t] = a[k][t];
        } else {
          fail = 1;
        }
      }
    }
  }

  if (!fail) {
    int cur = need[col] == -1 ? k - cnt : 1;
    for (int j = col + 1; j < m; j++) {
      if (need2[j] == -1) {
        cur = mul(cur, k);
      }
    }
    add(ans, cur);
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; i++) {
    a[i] = vector<int>(m);
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
      if (a[i][j] < 1 || a[i][j] > k) {
        printf("0\n");
        return 0;
      }
    }
  }
  sort(a, a + n);
  go(0, 0, n, vector<int>(m, -1));
  printf("%d\n", ans);
  return 0;
}
