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

const int MAXN = 80010;

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

int facs[MAXN];
int ifacs[MAXN];

int ank(int n, int k) {
  return mul(facs[n], ifacs[n - k]);
}

vector<vector<int>> words;
vector<pair<int, int>> d[MAXN];
int ans[MAXN];

int solve(const vector<pair<int, int>> & d) {
  int ans = 0;
  vector<int> s(2);
  vector<int> p(2);
  vector<int> sp(2);

  int last_p_id = -1;
  int last_p = -1;

  int cnt_all = 0;

  for (int i = 0; i < (int)d.size(); ) {
    int j = i + 1;
    while (j < (int)d.size() && d[j].first == d[j - 1].first && d[j].second == d[j-1].second + 1) j++;

    int len = j - i;
    bool prefix = d[i].second == 0;
    bool suffix = d[j - 1].second == (int)words[d[i].first].size() - 1;
    bool all = prefix && suffix;

    add(ans, mul(mul(mul(len, len + 1), ifacs[2]), facs[words.size()]));

    cnt_all += all;
    if (prefix) {
      add(p[all], len - all);
      last_p = len - all;
      last_p_id = d[i].first;
    }
    if (suffix) {
      add(s[all], len - all);
      if (last_p_id == d[i].first) {
        add(sp[all], mul(last_p, len - all));
      }
    }
    i = j;
  }

  for (int l = 2; l <= cnt_all; l++) {
    add(ans, mul(ank(cnt_all, l), facs[words.size() - l + 1]));
  }

  for (int l = 1; l <= cnt_all; l++) {
    add(ans, mul(s[0] + p[0], mul(ank(cnt_all, l), facs[words.size() - l])));
  }

  for (int l = 1; l <= cnt_all - 1; l++) {
    add(ans, mul(s[1] + p[1], mul(ank(cnt_all - 1, l), facs[words.size() - l])));
  }

  for (int l = 0; l <= cnt_all && l <= (int)words.size() - 2; l++) {
    int coef = mul(s[0], p[0]);
    sub(coef, sp[0]);
    add(ans, mul(coef, mul(ank(cnt_all, l), facs[words.size() - l - 1])));
  }

  for (int l = 0; l <= cnt_all - 1; l++) {
    int coef = mul(s[0], p[1]);
    add(coef, mul(s[1], p[0]));
    add(ans, mul(coef, mul(ank(cnt_all - 1, l), facs[words.size() - l - 1])));
  }

  for (int l = 0; l <= cnt_all - 2; l++) {
    int coef = mul(s[1], p[1]);
    sub(coef, sp[1]);
    add(ans, mul(coef, mul(ank(cnt_all - 2, l), facs[words.size() - l - 1])));
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  facs[0] = ifacs[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    facs[i] = mul(facs[i - 1], i);
    ifacs[i] = mpow(facs[i], MOD - 2);
  }


  int n;
  scanf("%d", &n);
  words.resize(n);
  for (auto &x : words) {
    int k;
    scanf("%d", &k);
    x.resize(k);
    for (int &y : x) {
      scanf("%d", &y);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int)words[i].size(); j++) {
      int x = words[i][j];
      for (int k = 1; k * k <= x; k++) {
        if (x % k == 0) {
          d[k].push_back({i, j});
          if (x / k != k) {
            d[x / k].push_back({i, j});
          }
        }
      }
    }
  }

  for (int i = 1; i < MAXN; i++) {
    ans[i] = solve(d[i]);
  }

  int res = 0;

  for (int i = MAXN - 1; i >= 1; i--) {
    for (int j = 2 * i; j < MAXN; j += i) {
      sub(ans[i], ans[j]);
    }
    add(res, mul(i, ans[i]));
  }

  eprintf("%d %d\n", ans[1], ans[2]);


  printf("%d\n", res);

  return 0;
}
