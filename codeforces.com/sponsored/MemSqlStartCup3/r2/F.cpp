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


const int MAXN = 62;

ll cnk[MAXN][MAXN];
char buf[200];

vector<ll> pleft[MAXN];
vector<ll> pright[MAXN];

void precalc(vector<ll> vals, vector<ll> *l, bool rev) {
  int n = vals.size();
  for (int i = 0; i < (1 << n); i++) {
    int cnt = 0;
    ll sum = 0;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        cnt++;
        sum += vals[j];
      }
    }
    l[cnt].push_back(sum);
  }
  for (int i = 0; i <= n; i++) {
    sort(l[i].begin(), l[i].end());
    if (rev) {
      reverse(l[i].begin(), l[i].end());
    }
  }
}

ll solve2(const vector<ll>& a, const vector<ll> &b, ll val) {
  ll cnt = 0;
  for (ll x : a) {
    for (ll y : b) {
      if (x + y == val) {
        cnt++;
      }
    }
  }
  return cnt;
  int p1 = 0;
  int p2 = 0;
  ll ans = 0;
  int asz = (int)a.size();
  int bsz = (int)b.size();
  while (p1 < asz && p2 < bsz) {
    if (a[p1] + b[p2] < val) {
      p1++;
    } else if (a[p1] + b[p2] > val) {
      p2++;
    } else {
      int cnta = 1;
      p1++;
      while (p1 < asz && a[p1] == a[p1 - 1]) {
        p1++, cnta++;
      }
      int cntb = 1;
      p2++;
      while (p2 < bsz && b[p2] == b[p2 - 1]) {
        p2++, cntb++;
      }
      ans += cnta * 1LL * cntb;
    }
  }
  return ans;
}

ll solve(ll need, int cnt) {
  ll ans = 0;
  for (int i = 0; i <= cnt; i++) {
    ans += solve2(pleft[i], pright[cnt - i], need);
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) cnk[i][j] += cnk[i - 1][j];
      if (i && j) cnk[i][j] += cnk[i - 1][j - 1];
    }
  }

  vector<ll> v;

  int r, c;
  scanf("%d%d", &r, &c);

  int as, bs;
  as = bs = r + c;

  for (int i = 0; i < 2 * (r + c); i++) {
    if (buf[i] == 'A') {
      as--;
    } else {
      bs--;
    }
    if (as >= r && bs >= r) {
      v.push_back(cnk[as][r] * cnk[bs][r]);
    } else {
      v.push_back(0);
    }
  }
  reverse(v.begin(), v.end());

  ll tot = cnk[2 * (r + c)][2 * c];

  {
    string ss = "ABAABBBA";
    ll tmp = 0;
    for (int i = 0; i < (int)ss.size(); i++) {
      if (ss[i] == 'A') {
        tmp += v[i];
      }
    }
    assert(tmp == tot / 2);
  }

  {
    int n = 2 * (r + c);
    ll ans = 0;
    for (int i = 0; i < (1 << n); i++) {
      if (__builtin_popcount(i) != n / 2) continue;
      ll tmp = 0;
      for (int j = 0; j < n; j++) {
        if (i & (1 << j)) {
          tmp += v[j];
        }
      }
      if (tmp == tot / 2) {
        ans++;
      }
    }
    printf("%lld\n", ans);
    return 0;
  }


  vector<ll> vv;
  int cnt = r + c;
  int zeros = 0;
  ll already = 0;
  scanf("%s", buf);
  for (int i = 0; i < 2 * (r + c); i++) {
    if (buf[i] == 'A') {
      already += v[i];
      cnt--;
    } else if (buf[i] == '?') {
      if (v[i] == 0) {
        zeros++;
      } else {
        vv.push_back(v[i]);
      }
    }
  }

  int lf = vv.size() / 2;

  precalc(vector<ll>(vv.begin(), vv.begin() + lf), pleft, false);
  precalc(vector<ll>(vv.begin() + lf, vv.end()), pright, true);

  scanf("%s", buf);
  ll ans = 0;
  for (ll need = tot / 2; need <= (tot + 1) / 2; need++) {
    for (int z = 0; z <= zeros; z++) {
      ans += solve(need - already, cnt - z);
    }
  }

  printf("%lld\n", ans);
  return 0;
}
