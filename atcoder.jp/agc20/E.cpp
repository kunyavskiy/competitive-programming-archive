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

map<pair<ll, int>, int> res;
map<string, int> res_s;

static inline ll bits(int l, int r) {
  return (1LL << r) - (1LL << l);
}

map<string, vector<string>> res_st;

const vector<string>& solve_stupid(string s) {
  if (res_st.count(s)) return res_st[s];
  if (s == "") {
    return res_st[s] = {""};
  }
  if (s == "0") {
    return res_st[s] = {"0"};
  }
  if (s == "1") {
    return res_st[s] = {"0", "1"};
  }
  vector<string> res;
  for (int i = 1; i < (int)s.size(); i++) {
    auto a = solve_stupid(s.substr(0, i));
    auto b = solve_stupid(s.substr(i));
    for (const string& aa : a) {
      for (const string& bb : b) {
        res.push_back(aa + bb);
      }
    }
  }
  for (int k = 2; k <= (int)s.size(); k++) {
    if (s.size() % k == 0) {
      string t(s.size() / k, '1');
      for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '0') {
          t[s[i] % k] = '0';
        }
      }
      auto a = solve_stupid(t);
      for (const string& aa : a) {
        char buf[10];
        sprintf(buf, "%d", k);
        res.push_back("(" + aa + "x" + buf + ")");
      }
    }
  }
  sort(res.begin(), res.end());
  res.erase(unique(res.begin(), res.end()), res.end());
  return res_st[s] = res;
}

ll ston(const string & s) {
  assert(s.size() <= 60);
  ll val = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    val = val + (((ll)(s[i] - '0')) << i);
  }
  return val;
}

string ntos(ll x, int n) {
  string res = "";
  for (int i = 0; i < n; i++) {
    res += char('0' + x % 2);
    x /= 2;
  }
  return res;
}

int solve(ll s, int n) {
  if (res.find({s, n}) != res.end()) {
    return res[{s, n}];
  }
  if (n == 0) {
    return 1;
  }
  int &ans = res[{s, n}];
  for (int k = 1; 2 * k <= n; k++) {
    ll ks = (1LL << k) - 1;
    ll val = s & ks;
    for (int j = 2 * k; j <= n; j += k) {
      val &= (s >> (j - k)) & ks;
      int res = solve(val, k);
      res = mul(res, solve(s >> j, n - j));
      add(ans, res);
    }
  }
  add(ans, solve(s >> 1, n - 1));
  if (s & 1) {
    add(ans, solve(s >> 1, n - 1));
  }
  return ans;
}

int solve(string s) {
  if (s.size() < 60) {
    return solve(ston(s), s.size());
  }
  if (res_s.find(s) != res_s.end()) {
    return res_s[s];
  }
  int n = s.size();
  int &ans = res_s[s];
  for (int k = 1; 2 * k <= n; k++) {
    string val = s.substr(0, k);
    for (int j = 2 * k; j <= n; j += k) {
      for (int t = j - k; t < j; t++) {
        if (s[t] == '0') {
          val[t % k] = '0';
        }
      }
      int res = solve(val);
      res = mul(res, solve(s.substr(j)));
      add(ans, res);
    }
  }
  add(ans, solve(s.substr(1)));
  if (s[0] == '1') {
    add(ans, solve(s.substr(1)));
  }
  return ans;
}


int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  string s;
  cin >> s;

  printf("%d\n", solve(s));

  return 0;
}
