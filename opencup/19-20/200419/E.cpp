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
#include <unordered_set>

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

map<pair<ll, ll>, int> cache;

int go(ll n, ll s, const vector<ll> &a) {
  if (n == 1) {
    return binary_search(a.begin(), a.end(), s);
  }
  if (n % 2 == 0) {
    if (s % 2 == 0) {
      return go(n / 2, s / 2, a);
    }
    return 0;
  }
  auto it = cache.find({n, s});
  if (it != cache.end()) {
    return it->second;
  }
  it = cache.insert(it, {{n, s}, 0});
  if (cache.size() % 100000 == 0) {
    eprintf("%d\n", (int)cache.size());
  }
  int ans = 0;
  for (ll x : a) {
    if (x > s) break;
    ans ^= go(n - 1, s - x, a);
  }
  return it->second = ans;
}

void solve() {
  //cache.clear();
  ll n, s;
  int k;
  scanf("%lld%lld%d", &n, &s, &k);
  vector<ll> a(k);
  for (ll& x : a) {
    scanf("%lld", &x);
  }
  // int res = go(n, s, a);
  vector<ll> data;
  data.push_back(s);
  while (n) {
    if (n % 2 == 0) {
      vector<ll> ndata;
      for (ll x : data) {
        if (x % 2 == 0) {
          ndata.push_back(x / 2);
        }
      }
      data = std::move(ndata);
    } else {
      const int N = 2.01e5;
      bitset<N> odd, even;

      if (data.empty()) {
        break;
      }
      ll mx = *max_element(data.begin(), data.end());
      for (ll x : data) {
        if (x % 2 == 0) {
          even[N - 1 - (mx - x)] = 1;
        } else {
          odd[N - 1 - (mx - x)] = 1;
        }
      }
      bitset<N> res;

      for (ll y : a) {
        if (y % 2 == 0) {
          res ^= even >> y;
        } else {
          res ^= odd >> y;
        }
      }

      data.clear();
      for (int i = 0; i < N; i++) {
        if (res[i]) {
          ll val = mx - (N - 1 - i);
          assert(val % 2 == 0);
          data.push_back(val / 2);
        }
      }
    }
//        eprintf("%d\n", (int)data.size());
    n /= 2;
  }
  if (!data.empty() && data[0] == 0) {
    printf("1\n");
  } else {
    printf("0\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
//    freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
