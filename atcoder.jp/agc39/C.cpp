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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

string read() {
  static char buf[(int)1e6];
  scanf("%s", buf);
  return buf;
}

bool dfs(int v, int k, int nc, int ncid, vector<int>& c, vector<int> &cid) {
  if (c[v] != -1) {
    return c[v] == nc;
  }
  c[v] = nc;
  cid[v] = ncid;
  if (!dfs((v + k) % c.size(), k, nc, ncid, c, cid)) return false;
  return dfs((v + c.size() / 2) % c.size(), k, nc ^ 1, ncid, c, cid);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int inv2 = minv(2);


  int n;
  while (scanf("%d", &n) == 1) {
    string x = read();
    for (int i = 0; i < n; i++) {
      x += '1';
    }

    n *= 2;
    vector<int> cnt(n + 1);
    for (int k = 1; k <= n; k++) {
      if (n % k != 0) continue;
      vector<int> c(n, -1);
      vector<int> cid(n);
      int cc = 0;
      bool fail = false;
      for (int i = 0; i < n; i++) {
        if (c[i] == -1) {
          if (!dfs(i, k, 0, cc++, c, cid)) {
            fail = true;
            break;
          }
        }
      }
      if (fail) continue;
      vector<vector<int>> pos(cc);
      for (int i = 0; i < n; i++) {
        pos[cid[i]].push_back(i);
      }

      int cur = mpow(2, cc);

      string nx(n, '?');
      for (int i = 0; ; i++) {
        if (i == n) {
          add(cnt[k], 1);
          break;
        }
        if (nx[i] == '?') {
          cur = mul(cur, inv2);
          if (x[i] == '0') {
            for (int p : pos[cid[i]]) {
              nx[p] = '0' + (c[p] ^ c[i]);
            }
          } else {
            add(cnt[k], cur);
            for (int p : pos[cid[i]]) {
              nx[p] = '0' + (c[p] ^ c[i] ^ 1);
            }
          }
        } else {
          if (nx[i] > x[i]) break;
          if (x[i] > nx[i]) {
            add(cnt[k], cur);
            break;
          }
        }
      }
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
      if (n % i) continue;
      for (int j = 2 * i; j <= n; j += i) {
        sub(cnt[j], cnt[i]);
      }
      eprintf("%d %d\n", i, cnt[i]);
      add(ans, mul(cnt[i], i));
    }

    printf("%d\n", ans);
  }


  return 0;
}
