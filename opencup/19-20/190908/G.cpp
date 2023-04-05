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

#define MOD 998244353

ll sum(ll a, ll b) { return (a + b) % MOD; }
ll mult(ll a, ll b) { return (a * b) % MOD; }

ll pw(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mult(res, a);
    }
    a = mult(a, a);
    b >>= 1;
  }
  return res;
}

ll inv(ll a) {
  return pw(a, MOD - 2);
}

vector<ll> fact_precalc(1, 1);
vector<ll> inv_fact_precalc(1, 1);

void ensure_fact(int n) {
  while (n >= (int)fact_precalc.size()) {
    fact_precalc.push_back(mult(fact_precalc.back(), fact_precalc.size()));
    inv_fact_precalc.push_back(inv(fact_precalc.back()));
//    cerr << "!" << fact_precalc.size() << " " << fact_precalc.back() << " " << inv_fact_precalc.back() << endl;
  }
}

ll fact(int n) {
  ensure_fact(n);
  return fact_precalc[n];
}

ll inv_fact(int n) {
  ensure_fact(n);

  return inv_fact_precalc[n];
}

ll calc_c(int n, int k) {
  ll res = fact(n);
  res = mult(res, inv_fact(k));
  res = mult(res, inv_fact(n - k));
//  cerr << n << " " << k << " " << res << endl;
  return res;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  string s;
  cin >> s;
  int n = s.size();
  long res = pw(2, n) - 1;

  bool ok = true;
  for (int i = 1; i < n; i++) {
    if (s[i] != s[i - 1]) ok = false;
  }
  if (ok) {
    cout << n << "\n";
    return 0;
  }

  for (int iii = 0; iii < 2; iii++) {
    for (int l = 0; l < n; l++) {
      if (l > 0 && s[l] == s[l - 1]) continue;
      int r = l + 1;
      while (r < n && s[r] == s[l]) r++;
      if (l > 0) {
        for (int m = l + 1; m <= r; m++) {
          ll x = calc_c(n - m + l - 1, l - 1);
          ll y = mult(x, pw(2, m - l) - 1);
          ll z = mult(x, (m - l));

//          cerr << s << " " << l << " " << m << " " << x << " " << y << " " << z << endl;

          res = sum(res, -y);
          res = sum(res, z);
        }
      }
    }
    reverse(s.begin(), s.end());
  }
  if (res < 0) res += MOD;
  cout << res << "\n";

  return 0;
}
