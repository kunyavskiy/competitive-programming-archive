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

vector<ll> get_dig(ll n, ll k) {
  vector<ll> a;
  while (n > 0) {
    a.push_back(n % k);
    n /= k;
  }
  return a;
}

int ccc = 0;
void solve_test() {
  ll k, l, r;
  scanf("%lld %lld %lld", &k, &l, &r);

  r++;

  auto ld = get_dig(l, k);
  auto rd = get_dig(r, k);
  while (ld.size() < rd.size()) ld.push_back(0);

  ll res = -1;
  ll mn = 0;
  ll mx = 0;
  for (int i = 0; i < (int)rd.size(); i++) {
    if (rd[i] > 0) {
      rd[i]--;
      bool ok = true;
      for (int j = (int)rd.size() - 1; j >= 0; j--) {
        if (rd[j] < ld[j]) {
          ok = false;
          break;
        } else if (rd[j] > ld[j]) {
          break;
        }
      }
      if (ok) {
        ll s = 0;
        for (long x : rd) s += x;
        s += rd.size();
        if (rd.back() == 0) s--;
        ll q = 0;
        for (int i = (int)rd.size() - 1; i >= 0; i--) {
          q = q * k + rd[i];
        }
        if (s > res) {
          res = s;
          mn = mx = q;
        } else if (s == res) {
          mn = min(mn, q);
          mx = max(mx, q);
        }
      }
    }
    rd[i] = k - 1;
  }
  ccc++;
  cout << "Case #" << ccc << ": " << res - 2 << " " << mn << " " << mx << "\n";
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0 ; i < n; i++) {
    solve_test();
  }

  return 0;
}
