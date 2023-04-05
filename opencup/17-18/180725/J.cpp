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

vector<int> solve_stupid(string s) {
  int n = (int)s.size();

  vector<vector<int>> d(n, vector<int>(1 << n, -1));
  queue<pair<int, int>> q;
  for (int i = 0; i < n; i++) {
    d[i][0] = 0;
    q.push({i, 0});
  }

  while (!q.empty()) {
    int v, mask;
    tie(v, mask) = q.front();
    q.pop();
    int cur = d[v][mask];

    mask ^= (1 << v);
    if (v > 0 && d[v - 1][mask] == -1) {
      d[v - 1][mask] = cur + 1;
      q.push({v - 1, mask});
    }
    if (v < n - 1 && d[v + 1][mask] == -1) {
      d[v + 1][mask] = cur + 1;
      q.push({v + 1, mask});
    }
  }

  int mask = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      mask |= (1 << i);
    }
  }

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = d[i][mask];
  }
  return ans;
}

vector<int> pref_odd[2];
vector<int> odd[2];


int solve_start(int p, int first_one, int last_one) {
  int ans = 0;
  int flip_l = min(first_one, p);
  int flip_r = p;

  ans += max(0, p - first_one);

  p = min(p, first_one);

  if (last_one == -1) {
    return ans;
  }

  if (p == last_one) {
    return ans + 3;
  }

  auto odd_flip = [&](int pos) {
    int l = min(flip_l, pos);
    int r = min(flip_r, pos);
    return odd[0][l] ^ odd[1][l] ^ odd[0][r] ^ odd[1][r] ^ odd[0][pos];
  };

  auto odd_pref_flip = [&](int l, int r) {
    int lf = min(flip_l, r);
    int rf = min(flip_r, r);
    // l .. lf; lf .. rf; rf .. r
    int ans = 0;
    ans += pref_odd[0][lf] - pref_odd[0][l];
    if ((odd[0][lf] ^ odd[1][lf]) == 0) {
      ans += pref_odd[1][rf] - pref_odd[1][lf];
    } else {
      ans += (rf - lf) - (pref_odd[1][rf] - pref_odd[1][lf]);
    }
    if ((odd[0][rf] ^ odd[0][lf] ^ odd[1][lf] ^ odd[1][rf]) == 0) {
      ans += pref_odd[0][r] - pref_odd[0][rf];
    } else {
      ans += (r - rf) - (pref_odd[0][r] - pref_odd[0][rf]);
    }
    return ans;
  };


  int real_last_one = last_one;
  if (odd_flip(last_one) == odd_flip(p)) {
    real_last_one -= 1;
  }

  if (odd_flip(p) == 1) {
    ans += real_last_one - p + 1;
    ans += 2 * odd_pref_flip(p, real_last_one + 1);
  } else {
    ans += 3 * (real_last_one - p + 1);
    ans -= 2 * odd_pref_flip(p, real_last_one + 1);
  }

  if (p != last_one) {
    ans -= 1;
  }

  return ans;
}

vector<int> solve_smarter(string s) {
  int n = s.size();
  vector<int> ans(n, 1 << 30);

  for (int _ = 0; _ < 2; _++) {
    int first_one = -1;
    int last_one = -1;
    for (int i = 0; i < (int) s.size(); i++) {
      if (s[i] == '1') {
        first_one = i;
        break;
      }
    }
    if (first_one == -1) return vector<int>(s.size(), 0);

    for (int i = 0; i < (int) s.size(); i++) {
      if (s[i] == '1') {
        last_one = i;
      }
    }

    pref_odd[0] = pref_odd[1] = vector<int>(s.size() + 1, 0);
    odd[0] = odd[1] = vector<int>(s.size() + 1, 0);

    int cur[2];
    cur[0] = cur[1] = 0;

    for (int i = 0; i < (int)s.size(); i++) {
      cur[s[i] - '0'] ^= 1;
      odd[0][i + 1] = cur[0];
      odd[1][i + 1] = cur[1];
      pref_odd[0][i + 1] = pref_odd[0][i] + cur[0];
      pref_odd[1][i + 1] = pref_odd[1][i] + cur[1];
    }

    string sb = s;

    for (int i = 0; i < n; i++) {
      if (i > first_one) {
        s[i - 1] ^= 1;
      }
      if (i - 1 == last_one) {
        last_one = -1;
        for (int j = 0; j < (int) s.size(); j++) {
          if (s[j] == '1') {
            last_one = j;
          }
        }
      }
      if (i - 1 > last_one && s[i - 1] == '1') {
        last_one = i - 1;
      }
      ans[i] = min(ans[i], solve_start(i, first_one, last_one));
    }

    s = sb;

    reverse(s.begin(), s.end());
    reverse(ans.begin(), ans.end());
  }


  return ans;
}


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

void solve() {
  static char buf[1000100];
  int n;
  scanf("%d%s", &n, buf);


  vector<int> ans = solve_smarter(buf);
  vector<int> ans_stupid = ans;//solve_stupid(buf);

  if (ans != ans_stupid) {
    eprintf("%s\n", buf);
    eprintf("correct:");
    for (int i = 0; i < n; i++) {
      eprintf(" %d", ans_stupid[i]);
    }
    eprintf("\nsmart:");
    for (int i = 0; i < n; i++) {
      eprintf(" %d", ans[i]);
    }
    eprintf("\n");
    assert(0);
  }

  int res = 0;
  for (int i = 0; i < n; i++) {
    add(res, mul(ans[i], i + 1));
  }
  printf("%d\n", res);
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }


  return 0;
}
