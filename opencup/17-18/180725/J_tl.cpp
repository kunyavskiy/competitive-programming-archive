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

int solve_start(string s, int p) {
  int first_one = -1;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] == '1') {
      first_one = i;
      break;
    }
  }
  if (first_one == -1) return 0;

  int ones = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] == '1') {
      ones += 1;
    }
  }


  int ans = 0;
  auto flip = [&s, &ones, &ans](int i) {
    ++ans;
    if (s[i] == '1') {
      s[i] = '0';
      ones--;
    } else {
      s[i] = '1';
      ones++;
    }
  };

  while (p > first_one) {
    flip(--p);
  }

  while (ones > 0) {
    if (s[p] == '0') {
      flip(++p);
    } else {
      flip(++p);
      flip(--p);
      if (ones != 0) {
        flip(++p);
      }
    }
  }
  return ans;
}

vector<int> solve_smarter(string s) {
  int n = s.size();
  vector<int> ans(n);

  for (int i = 0; i < n; i++) {
    ans[i] = solve_start(s, i);
  }

  reverse(s.begin(), s.end());

  for (int i = 0; i < n; i++) {
    ans[n - i - 1] = min(ans[n - i - 1], solve_start(s, i));
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
  static char buf[1'000'100];
  int n;
  scanf("%d%s", &n, buf);

  vector<int> ans_stupid = solve_stupid(buf);

  vector<int> ans = solve_smarter(buf);

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
