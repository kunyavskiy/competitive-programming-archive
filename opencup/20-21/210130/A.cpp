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

int norm(int a, int mod) {
  if (a >= mod) a -= mod;
  return a;
}

struct Hash {
  static constexpr int MOD1 = 1'000'000'007;
  static constexpr int MOD2 = 1'000'000'009;
  int v1, v2;
  explicit Hash(int v = 0) : Hash(v, v) {}
  Hash(int v1, int v2) : v1(v1), v2(v2) {}
  bool operator==(const Hash &rhs) const {
    return std::tie(v1, v2) == std::tie(rhs.v1, rhs.v2);
  }
  bool operator!=(const Hash &rhs) const {
    return !(rhs == *this);
  }
};


Hash operator+(const Hash& a, const Hash &b) {
  return {norm(a.v1 + b.v1, Hash::MOD1), norm(a.v2 + b.v2, Hash::MOD2)};
}

Hash operator-(const Hash& a, const Hash &b) {
  return {norm(a.v1 - b.v1 + Hash::MOD1, Hash::MOD1), norm(a.v2 - b.v2 + Hash::MOD2, Hash::MOD2)};
}

Hash operator*(const Hash& a, const Hash &b) {
  return {(int)(a.v1 * 1LL * b.v1 % Hash::MOD1), (int)(a.v2 * 1LL * b.v2 % Hash::MOD2) };
}

Hash P{239};
vector<Hash> degs;


struct hasher {
  vector<Hash> v;
  explicit hasher(const string& s) {
    v.resize(s.size() + 1);
    for (int i = 0; i < (int)s.size(); i++) {
      v[i + 1] = v[i] * P + Hash{s[i]};
    }
  }
  Hash getHash(int l, int r) {
    return v[r] - v[l] * degs[r - l];
  }
};

void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  static char buf[1'100'000];
  string s, t;
  scanf("%s", buf); s = buf;
  scanf("%s", buf); t = buf;
  if (abs((int)s.size() - (int)t.size()) > k) {
    printf("NO\n");
    return;
  }
  while ((int)degs.size() <= n || (int)degs.size() <= m) {
    degs.push_back(degs.back() * P);
  }


  hasher h1(s);
  hasher h2(t);
  auto lcp = [&](int a, int b) {
    int l = 0;
    int r = min(n - a, m - b) + 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (h1.getHash(a, a + mid) == h2.getHash(b, b + mid)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    return l;
  };
  vector<vector<int>> dp_(k + 1, vector<int>(2 * k + 1, -1));

  auto dp = [&](int i, int j) -> int& {
    return dp_[i][j + k];
  };
  dp(0,0) = lcp(0, 0);

  auto relax = [](int& a, int b) {
    a = max(a, b);
  };

  for (int ans = 0; ans < k; ans++) {
    for (int diff = -ans; diff <= ans; diff++) {
      if (dp(ans, diff) == -1) continue;
      int pos1 = dp(ans, diff);
      int pos2 = dp(ans, diff) - diff;
      relax(dp(ans + 1, diff), dp(ans, diff));
      if (pos1 < n && pos2 < m) {
        relax(dp(ans + 1, diff), pos1 + 1 + lcp(pos1 + 1, pos2 + 1));
      }
      if (pos1 < n) {
        relax(dp(ans + 1, diff + 1), pos1 + 1 + lcp(pos1 + 1, pos2));
      }
      if (pos2 < m) {
        relax(dp(ans + 1, diff - 1), pos1 + lcp(pos1, pos2 + 1));
      }
    }
  }

  if (dp(k,n - m) < n) {
    printf("NO\n");
    return;
  }
  printf("YES\n");
  int ans = k;
  while (ans && dp(ans - 1, n - m) == n) {
    ans--;
  }
  vector<string> ops;
  while (n || m) {
    assert(dp(ans, n - m) >= n);
    if (n && m && s[n - 1] == t[m - 1]) {
      n--;
      m--;
    } else if (n && m && dp(ans - 1, n - m) >= n - 1) {
      ops.push_back("REPLACE " + to_string(n) + " " + t[m - 1]);
      n--;
      m--;
      ans--;
    } else if (n && abs(n - m - 1) <= k && dp(ans - 1, n - m - 1) >= n - 1) {
      ops.push_back("DELETE " + to_string(n));
      n--;
      ans--;
    } else if (m && abs(n - m + 1) <= k && dp(ans - 1, n - m + 1) >= n) {
      ops.push_back("INSERT " + to_string(n + 1) + " " + t[m - 1]);
      m--;
      ans--;
    } else {
      assert(0);
    }
  }

  printf("%d\n", (int)ops.size());
  for (const string& ss : ops) {
    printf("%s\n", ss.c_str());
  }
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif
  degs.emplace_back(1);

  int z;
  scanf("%d", &z);
  while (z-->0) {
    solve();
  }


  return 0;
}
