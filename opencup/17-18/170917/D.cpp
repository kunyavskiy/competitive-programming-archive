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

char s[100];

const long long INF = 1LL << 62;

ll bin2dec(string s) {
  ll val = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    val = val * 2 + s[i] - '0';
  }
  return val;
}

string dec2bin(ll x) {
  string s = "";
  while (x) {
    char c = '0' + (x % 2);
    s += c;
    x /= 2;
  }
  reverse(s.begin(), s.end());
  return s;
}

string dec2bin(ll x, int len) {
  string s = "";
  while (len-- > 0) {
    char c = '0' + (x % 2);
    s += c;
    x /= 2;
  }
  reverse(s.begin(), s.end());
  return s;
}


ll before(ll x) {
  ll res = 0;
  ll prev = 1;
  for (int i = 1;; i++) {
    ll limit = (1LL << i);
    if (limit > x) {
      return res + (x - prev) * i;
    }
    res += (limit - prev) * i;
    prev = limit;
  }
  assert(0);
}

ll solve(ll val, string s) {
  if (val <= 0) return INF;
  string rg = "";
  for (ll x = val; rg.size() < s.size(); x++) {
    rg += dec2bin(x);
  }
  string lf = "";
  for (ll x = val - 1; lf.size() < s.size() && x > 0; x--) {
    lf = dec2bin(x) + lf;
  }
  string ss = lf + rg;
  ll pos = before(val) - lf.size();
  size_t f = ss.find(s);
  if (f == string::npos) {
    return INF;
  }
//  eprintf("%lld %s -> %lld\n", val, s.c_str(), pos + f);
  return pos + f + s.size();
}

ll solve_slow(string s) {
  string r = "";
  for (int i = 1; i <= (1 << ((int)s.size() + 1)); i++) {
    r += dec2bin(i);
  }
  ll res = r.find(s) + s.size();
  eprintf("! %s %lld\n", s.c_str(), res);
  return res;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  while (scanf("%s", s) == 1) {
    int n = strlen(s);
    string a = string(s) + string(s);
    ll res = INF;
    res = min(res, solve(bin2dec("1" + string(s)), s));
    for (int i = 0; i < 2 * n; i++) {
      for (int j = 1; j <= n; j++) {
        ll val = bin2dec(a.substr(i, j));
        res = min(res, solve(val, s));
        res = min(res, solve(val - 1, s));
      }
    }
    for (int i = 1; i < n; i++) {
      string x = string(s).substr(i);
      string y = string(s).substr(0, i);
      y = dec2bin(bin2dec(y) + 1, y.size());
      for (int j = 0; j <= (int)y.size(); j++) {
        ll val = bin2dec(x + y.substr(j));
        res = min(res, solve(val, s));
        res = min(res, solve(val - 1, s));
      }
    }
//    eprintf("res = %lld\n", res);
    assert(res == solve_slow(s));
    printf("%lld\n", res);
  }

  return 0;
}
