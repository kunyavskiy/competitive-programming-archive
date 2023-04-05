#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

char s[2][1'100'000];

char buf[128'000'000];
int buf_ptr = 0;

void * operator new(size_t size) {
  void *res = buf + buf_ptr;
  buf_ptr += size;
  return res;
}

void operator delete(void *) {}
void operator delete(void *, size_t) {}

struct my_set {
  multiset<ll> s;
  ll diff = 0;

  void insert(ll x) {
    s.insert(x - diff);
  }
  void erase(ll x) {
    auto it = s.find(x - diff);
    assert(it != s.end());
    s.erase(it);
  }
  void add(ll v) {
    diff += v;
  }
  ll get_min() {
    return *s.begin() + diff;
  }
  ll get_max() {
    return *s.rbegin() + diff;
  }

  int size() {
    return (int)s.size();
  }

  vector<ll> get_all() {
    vector<ll> ans;
    ans.reserve(s.size());
    for (ll x : s) {
      ans.push_back(x + diff);
    }
    return ans;
  }

};

void solve() {
  int n;
  ll t0, t1, ts;
  scanf("%d%lld%lld%lld", &n, &t0, &t1, &ts);

  scanf("%s%s", s[0], s[1]);
  auto conv = [](int x) {
    if ('0' <= x && x <= '9') {
      return x - '0';
    }
    return x - 'A' + 10;
  };
  auto get = [&](int str, int pos) {
    int ch = pos / 4;
    int bit = (3 - pos % 4);
    return (conv(s[str][ch]) >> bit) & 1;
  };

  n *= 4;

  my_set s1, s2;
  int cntl, cntr;
  cntl = cntr = 0;

  ll base = 0;

  auto add = [&](ll val) {
    if (s1.size() == 0 || s1.get_max() < val) {
      s2.insert(val);
    } else {
      s1.insert(val);
    }
  };

#ifdef LOCAL
  auto dump = [&]() {
    vector<ll> s1v = s1.get_all();
    vector<ll> s2v = s2.get_all();
    s1v.insert(s1v.end(), s2v.begin(), s2v.end());
    ll bc = base;
    eprintf("%d %d: %lld", cntl, cntr, base);
    for (ll x : s1v) {
      bc += x;
      eprintf(" %lld", bc);
    }
    eprintf("\n");
  };
  dump();
#endif

  // 2 0
  // -2

  for (int i = 0; i < n; i++) {
    if (get(0, i)) {
      add(-t1);
      cntr++;
      base += t1;
    }
//    dump();
    if (get(1, i)){
      add(t0);
      cntl++;
    }
//    dump();
    while (s1.size() < cntl) {
      ll v = s2.get_min();
      s1.insert(v);
      s2.erase(v);
    }
//    dump();
    while (s1.size() > cntl) {
      ll v = s1.get_max();
      s1.erase(v);
      s2.insert(v);
    }
//    dump();
    base += ts * cntl;
    s1.add(-ts);
    s2.add(ts);
//    dump();
  }

  auto to_add = s1.get_all();
//  eprintf("ololo\n");
  printf("%lld\n", accumulate(to_add.begin(), to_add.end(), base));
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
