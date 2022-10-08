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

int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD)
    a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0)
    a += MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) { return mpow(x, MOD - 2); }

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  while (scanf("%d%d", &n, &MOD) == 2) {
    vector<int> fs(3 * n + 1);
    vector<int> ifs(3 * n + 1);
    vector<int> ip2(3 * n + 1);
    vector<int> ip3(3 * n + 1);
    fs[0] = ifs[0] = ip2[0] = ip3[0] = 1;
    int inv2 = minv(2);
    int inv3 = minv(3);
    for (int i = 1; i <= 3 * n; i++) {
      fs[i] = mul(fs[i - 1], i);
      ifs[i] = mul(ifs[i - 1], minv(i));
      ip2[i] = mul(ip2[i - 1], inv2);
      ip3[i] = mul(ip3[i - 1], inv3);
    }

#ifdef LOCAL
    {
      vector<int> v(6);
      for (int i = 0; i < 6; i++)
        v[i] = i;
      int tmp[7][7][7];
      memset(tmp, 0, sizeof(tmp));
      do {
        bool ok = true;
        int cnt[3] = {0, 0, 0};
        for (int i = 0; i < 6; ) {
          int j = i;
          while (j < 6 && v[j] <= v[i]) j++;
          if (j - i > 3) {
            ok = false;
          } else {
            cnt[j - i - 1]++;
          }
          i = j;
        }
        if (ok && cnt[0] >= cnt[1]) {
          tmp[cnt[0]][cnt[1]][cnt[2]]++;
        }
      } while (next_permutation(v.begin(), v.end()));
      int tot = 0;
      for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 6; j++) {
          for (int k = 0; k <= 6; k++) {
            if (tmp[i][j][k]) {
              tot += tmp[i][j][k];
              eprintf("%d %d %d %d\n", i, j, k, tmp[i][j][k]);
            }
          }
        }
      }
      eprintf("tot = %d\n======\n", tot);
    }
#endif

    int ans = 0;
    for (int cnt1 = 0; cnt1 <= 3 * n; cnt1++) {
      for (int cnt2 = 0; cnt1 + 2 * cnt2 <= 3 * n && cnt2 <= cnt1; cnt2++) {
        int cnt3 = 3 * n - cnt1 - 2 * cnt2;
        if (cnt3 % 3 != 0) {
          continue;
        }
        cnt3 /= 3;


        int cur = fs[3 * n];
        cur = mul(cur, ip2[cnt2]);
        cur = mul(cur, ip3[cnt3]);
        cur = mul(cur, ifs[cnt1]);
        cur = mul(cur, ifs[cnt2]);
        cur = mul(cur, ifs[cnt3]);
        eprintf("%d %d %d %d\n", cnt1, cnt2, cnt3, cur);

        add(ans, cur);
      }
    }

    printf("%d\n", ans);

  }

  return 0;
}
