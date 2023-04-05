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
#include <unordered_map>

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

vector<ll> a;

ll gcd(ll a, ll b) {
  while (b) {
    ll t = a % b;
    a = b;
    b = t;
  }
  return a;
}

const int MAXN = 1000001;

int mind[MAXN];
vector<int> primes;

void gen_primes(int n) {
  mind[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (mind[i] == 0) {
      mind[i] = i;
      primes.push_back(i);
    }
    for (int j : primes) {
      if (j > mind[i] || i * j > n) break;
      mind[i * j] = j;
    }
  }
}

unordered_map<ll, int> divs;

void gen_divs(const vector<pair<ll, int>>& a, int pos, ll val) {
  if (pos == (int)a.size()) {
    divs[val]++;
    return;
  }
  for (int i = 0; i <= a[pos].second; i++) {
    gen_divs(a, pos + 1, val);
    val *= a[pos].first;
  }
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  gen_primes(MAXN - 1);

  int n, k;
  scanf("%d %d", &n, &k);
  a.resize(n);

  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }

  vector<pair<ll, int>> ua;

  sort(a.begin(), a.end());
  for (int i = 0; i < n; ) {
    int j = i;
    while (j < n && a[i] == a[j]) j++;
    ua.push_back({a[i], j - i});
    i = j;
  }

  random_shuffle(a.begin(), a.end());

  const int MAGIC = 80;

  for (int i = 0; i < MAGIC && i < n; i++) {
    vector<pair<ll, int>> p;
    ll x = a[i];
    for (int j : primes) {
      int c = 0;
      while (x % j == 0) {
        x /= j;
        c++;
      }
      if (c) {
        p.push_back({j, c});
      }
      if (x == 1) break;
    }
    if (x != 1) {
      eprintf("!!!\n");
      for (auto u : ua) {
        ll g = gcd(u.first, x);
        if (g != 1 && g != x) {
          if (g != x / g) {
            p.push_back({g, 1});
            p.push_back({x / g, 1});
          } else {
            p.push_back({g, 2});
          }
          x = 1;
          break;
        }
      }
      if (x != 1) {
        p.push_back({x, 1});
      }
    }

    gen_divs(p, 0, 1);
  }

  TIMESTAMP("divs");

  int tr = 16;
  if (n <= MAGIC) {
    tr = n - k;
  }

  vector<pair<ll, int>> mdivs(divs.begin(), divs.end());
  sort(mdivs.begin(), mdivs.end());

  for (auto it = mdivs.rbegin();; it++) {
    assert(it != mdivs.rend());
    if (it->second < tr) continue;
    int cnt = 0;
    for (auto x : ua) {
      if (x.first % it->first == 0) {
        cnt += x.second;
      }
    }
    if (cnt >= n - k) {
      printf("%lld\n", it->first);
      return 0;
    }
  }
  assert(0);
}
